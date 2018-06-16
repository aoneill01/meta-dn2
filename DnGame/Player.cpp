#include <Gamebuino-Meta.h>
#include "Player.h"

#define PRECISION 6
#define GRAVITY 0x8
#define ALMOST_ONE 0b111111

#define velocityInPixelsPerFrame(val) (val << PRECISION >> 1)

void Player::resetPosition(Level &l) {
  x = (10 * 8) << PRECISION;
  y = (10 * 8) << PRECISION;
}

int Player::getX() {
  return x >> PRECISION;
}

int Player::getY() {
  return y >> PRECISION;
}

void Player::update(Level &level) {
  internalUpdate(level, true);
  PlayerState newState = internalUpdate(level, false);

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

PlayerState Player::internalUpdate(Level &level, bool firstUpdate) {
  if (wallJumpDelay) {
    wallJumpDelay--;
  }
  else {
    velX = 0;
  }
  
  if (gb.buttons.repeat(Button::right, 0) && !wallJumpDelay) {
    facingLeft = false;
    velX = velocityInPixelsPerFrame(3);
  }
  if (gb.buttons.repeat(Button::left, 0) && !wallJumpDelay) {
    facingLeft = true;
    velX = velocityInPixelsPerFrame(-3);
  }

  if (gb.buttons.pressed(Button::a)) {
    if (touchingGround) {
      velY = velocityInPixelsPerFrame(-10);
    }
    else if (touchingRightWall || touchingLeftWall) {
      velY = velocityInPixelsPerFrame(-6);
      wallJumpDelay = 20;
      if (touchingRightWall) {
        velX = velocityInPixelsPerFrame(-4);
        facingLeft = true;
      }
      else {
        velX = velocityInPixelsPerFrame(4);
        facingLeft = false;
      }
    }
  }
  
  x += velX;
  if (level.collisionAt(x >> PRECISION, y >> PRECISION, getWidth(), getHeight())) {
    wallJumpDelay = 0;

    int backOne = velX > 0 ? velocityInPixelsPerFrame(-1) : velocityInPixelsPerFrame(1);
    
    do {
      x += backOne;
    } 
    while(level.collisionAt(x >> PRECISION, y >> PRECISION, getWidth(), getHeight()));
  }

  touchingGround = level.collisionAt(x >> PRECISION, ((y  + 1) >> PRECISION), getWidth(), getHeight());
  touchingRightWall = !touchingGround && velY > 0 && gb.buttons.repeat(Button::right, 0) && level.collisionAt((x + velocityInPixelsPerFrame(1)) >> PRECISION, y >> PRECISION, getWidth(), getHeight());
  touchingLeftWall = !touchingGround && velY > 0 && gb.buttons.repeat(Button::left, 0) && level.collisionAt((x + velocityInPixelsPerFrame(-1)) >> PRECISION, y >> PRECISION, getWidth(), getHeight());

  velY += (touchingRightWall || touchingLeftWall) && velY > 0 ? GRAVITY >> 2 : GRAVITY;
  if (velY > 4 * ALMOST_ONE) velY = 4 * ALMOST_ONE;
  if (velY < 4 * -ALMOST_ONE) velY = 4 * -ALMOST_ONE;
  y += velY;
  if (level.collisionAt(x >> PRECISION, y >> PRECISION, getWidth(), getHeight())) {
    wallJumpDelay = 0;

    int backOne = velY > 0 ? velocityInPixelsPerFrame(-1) : velocityInPixelsPerFrame(1);
    velY = 0;
    y = y | ALMOST_ONE;
    do {
      y += backOne;
    }
    while(level.collisionAt(x >> PRECISION, y >> PRECISION, getWidth(), getHeight()));
  }

  if (touchingGround) {
    velY = 0;
    if (gb.buttons.repeat(Button::right, 0) || gb.buttons.repeat(Button::left, 0)) {
      return PlayerState::Run;
      //animationFrame = 4 + ((gb.frameCount / 4) % 8);
    }
    else {
      return PlayerState::Idle;
      //animationFrame = ((gb.frameCount / 4) % 4);
    }
  }
  else {
    if (touchingRightWall || touchingLeftWall) {
      return PlayerState::Wall;
      //animationFrame = 12;
    }
    else {
      return velY > velocityInPixelsPerFrame(1) ? PlayerState::Fall : PlayerState::Jump;
      //animationFrame = 14 + ((gb.frameCount / 4) % 2);
    }
  }
}
