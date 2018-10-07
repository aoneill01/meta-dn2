#include <Gamebuino-Meta.h>
#include "Player.h"
#include "TileSet.h"
#include "BreakableBlocks.h"

const SQ15x16 _gravity = 0.125;
const SQ15x16 _almostOne = .999;

void Player::resetPosition(Level &l) {
  x = 10 * 8;
  y = 10 * 8;
  velX = velY = 0;
}

int Player::getX() {
  return x.getInteger();
}

int Player::getY() {
  return y.getInteger();
}

bool Player::isDead() {
  return state == PlayerState::Dead;
}

void Player::update(Level &level, BreakableBlocks &breakableBlocks) {
  // Two internal updates per drawn frame
  PlayerState newState = internalUpdate(level, breakableBlocks, true);
  
  if (newState != PlayerState::Dead) {
    newState = internalUpdate(level, breakableBlocks, false);
  }

  sameStateCount++;
  if (newState != state) sameStateCount = 0;
  state = newState;
  switch (state) {
    case PlayerState::Run:
      animationFrame = 4 + (((sameStateCount / 4) + 1) % 8);
      break;
    case PlayerState::Idle:
      animationFrame = 0 + ((sameStateCount / 4) % 4);
      break;
    case PlayerState::Jump:
      animationFrame = 14 + ((sameStateCount / 4) % 2);
      break;
    case PlayerState::Fall:
      animationFrame = 16 + ((sameStateCount / 4) % 2);
      break;
    case PlayerState::Wall:
      animationFrame = sameStateCount < 4 ? 13 : 12;
      break;
  }
}

PlayerState Player::internalUpdate(Level &level, BreakableBlocks &breakableBlocks, bool firstUpdate) {
  bool dead = false;
  TileSet collidedTiles;
  
  if (wallJumpDelay) {
    wallJumpDelay--;
  }
  else {
    velX = 0;
  }

  // Handle button presses
  if (gb.buttons.repeat(Button::right, 0) && !wallJumpDelay) {
    facingLeft = false;
    velX = 1.5;
  }
  if (gb.buttons.repeat(Button::left, 0) && !wallJumpDelay) {
    facingLeft = true;
    velX = -1.5;
  }

  if (gb.buttons.pressed(Button::a)) {
    if (touchingGround) {
      velY = -10;
    }
    else if (touchingRightWall || touchingLeftWall) {
      velY = -6;
      wallJumpDelay = 20;
      if (touchingRightWall) {
        velX = -2;
        facingLeft = true;
      }
      else {
        velX = 2;
        facingLeft = false;
      }
    }
  }

  // Handle horizontal movement
  x += velX;
  if (level.collisionsAt(getX(), getY(), getWidth(), getHeight(), collidedTiles)) {
    wallJumpDelay = 0;

    int backOne = velX > 0 ? -1 : 1;
    
    do {
      x += backOne;
    } 
    while(level.collisionsAt(getX(), getY(), getWidth(), getHeight(), collidedTiles));

    if (level.collisionsAt(getX() - backOne, getY(), getWidth(), getHeight(), collidedTiles) && collidedTiles.containsTile(2)) {
      dead = true;
    }
  }

  // Handle vertical movement
  velY += (touchingRightWall || touchingLeftWall) && velY > 0 ? _gravity / 4 : _gravity;
  if (velY > 4 * _almostOne) velY = 4 * _almostOne;
  if (velY < 4 * -_almostOne) velY = 4 * -_almostOne;
  y += velY;
  if (level.collisionsAt(getX(), getY(), getWidth(), getHeight(), collidedTiles)) {
    wallJumpDelay = 0;

    int backOne = velY > 0 ? -1 : 1;
    velY = 0;
    y = y.getInteger() + _almostOne;
    do {
      y += backOne;
    }
    while(level.collisionsAt(getX(), getY(), getWidth(), getHeight(), collidedTiles));

    if (level.collisionsAt(getX(), getY() - backOne, getWidth(), getHeight(), collidedTiles) && collidedTiles.containsTile(2)) {
      dead = true;
    }
  }

  touchingGround = level.collisionsAt(getX(), getY() + 1, getWidth(), getHeight(), collidedTiles);
  for (int i = 0; i < collidedTiles.getCount(); i++) {
    TileInfo ti = collidedTiles.getTileInfo(i);
    if (ti.tile == 3) {
      breakableBlocks.triggerBlockAt(ti.x, ti.y);
    }
  }
  touchingRightWall = !touchingGround && velY > 0 && gb.buttons.repeat(Button::right, 0) && level.collisionsAt(getX() + 1, getY(), getWidth(), getHeight(), collidedTiles);
  touchingLeftWall = !touchingGround && velY > 0 && gb.buttons.repeat(Button::left, 0) && level.collisionsAt(getX() - 1, getY(), getWidth(), getHeight(), collidedTiles);

  // Return the current player state based on the update
  if (dead) return PlayerState::Dead;
  if (touchingGround) {
    velY = 0;
    if (gb.buttons.repeat(Button::right, 0) || gb.buttons.repeat(Button::left, 0)) {
      return PlayerState::Run;
    }
    else {
      return PlayerState::Idle;
    }
  }
  else {
    if (touchingRightWall || touchingLeftWall) {
      return PlayerState::Wall;
    }
    else {
      return velY > 1 ? PlayerState::Fall : PlayerState::Jump;
    }
  }
}
