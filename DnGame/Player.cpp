#include <Gamebuino-Meta.h>
#include "Player.h"
#include "TileSet.h"
#include "BreakableTiles.h"

SQ15x16 _normalGravity = 0.18;
SQ15x16 _jumpGravity = 0.09;
SQ15x16 _jumpVel = -3.55;
SQ15x16 _maxRunVel = 1.8;
SQ15x16 _wallVelX = 1.8;
SQ15x16 _wallVelY = -2.4;
SQ15x16 _maxFallVelY = 4;
SQ15x16 _runAcc = 0.13;
SQ15x16 _runDec = 0.18;
const SQ15x16 _almostOne = .999;

void Player::resetPosition(Level &l) {
  x = 31 * 16 + 8;
  y = 0;
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

void Player::handleTick(Level &level, BreakableTiles &breakableTiles) {
  // Two internal updates per drawn frame
  PlayerState newState = internalUpdate(level, breakableTiles, true);
  
  if (newState != PlayerState::Dead) {
    newState = internalUpdate(level, breakableTiles, false);
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

PlayerState Player::internalUpdate(Level &level, BreakableTiles &breakableTiles, bool firstUpdate) {
  bool dead = false;
  TileSet collidedTiles;
  SQ15x16 gravity = _normalGravity;
  
  if (wallJumpDelay) {
    wallJumpDelay--;
  }
  else {
    // velX = 0;
  }

  // Handle button presses
  if (!wallJumpDelay) {
    if (gb.buttons.repeat(Button::right, 0)) {
      facingLeft = false;
      velX += _runAcc;
      if (velX > _maxRunVel) velX = _maxRunVel;
    }
    else if (gb.buttons.repeat(Button::left, 0)) {
      facingLeft = true;
      velX -= _runAcc;
      if (velX < -_maxRunVel) velX = -_maxRunVel;
    }
    else {
      if (velX > 0) {
        velX -= _runDec;
        if (velX < 0) velX = 0;
      }
      else {
        velX += _runDec;
        if (velX > 0) velX = 0;
      }
    }
  }

  if (gb.buttons.pressed(Button::a)) {
    if (touchingGround) {
      velY = _jumpVel;
    }
    else if (touchingRightWall || touchingLeftWall) {
      velY = _wallVelY;
      wallJumpDelay = 20;
      if (touchingRightWall) {
        velX = -_wallVelX;
        facingLeft = true;
      }
      else {
        velX = _wallVelX;
        facingLeft = false;
      }
    }
    
  }
  if (gb.buttons.repeat(Button::a, 0)) {
    if (velY < 0) gravity = _jumpGravity;
  }

  if (firstUpdate && gb.buttons.repeat(Button::b, 0)) {
    if (gb.buttons.pressed(Button::up)) {
      _runAcc *= 1.05;
      SerialUSB.print("_runAcc: ");
      SerialUSB.println(static_cast<float>(_runAcc));
    }
    if (gb.buttons.pressed(Button::down)) {
      _runAcc *= 0.95;
      SerialUSB.print("_runAcc: ");
      SerialUSB.println(static_cast<float>(_runAcc));
    }
    if (gb.buttons.pressed(Button::right)) {
      _runDec *= 1.05;
      SerialUSB.print("_runDec: ");
      SerialUSB.println(static_cast<float>(_runDec));
    }
    if (gb.buttons.pressed(Button::left)) {
      _runDec *= 0.95;
      SerialUSB.print("_runDec: ");
      SerialUSB.println(static_cast<float>(_runDec));
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

    if (level.collisionsAt(getX() - backOne, getY(), getWidth(), getHeight(), collidedTiles) && collidedTiles.containsTile(PROP_DEATH)) {
      dead = true;
    }
  }

  // Handle vertical movement
  velY += (touchingRightWall || touchingLeftWall) && velY > 0 ? gravity / 4 : gravity;
  if (velY > _maxFallVelY) velY = _maxFallVelY;
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

    if (level.collisionsAt(getX(), getY() - backOne, getWidth(), getHeight(), collidedTiles) && collidedTiles.containsTile(PROP_DEATH)) {
      dead = true;
    }
  }

  touchingGround = level.collisionsAt(getX(), getY() + 1, getWidth(), getHeight(), collidedTiles);
  for (int i = 0; i < collidedTiles.getCount(); i++) {
    TileInfo ti = collidedTiles.getTileInfo(i);
    if (ti.propety == PROP_BREAK) {
      breakableTiles.triggerBlockAt(ti.x, ti.y);
    }
  }
  nextLevel = collidedTiles.containsTile(PROP_DOWN);
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
