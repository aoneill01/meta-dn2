#include <Gamebuino-Meta.h>
#include "Player.h"

#define PRECISION 6
#define GRAVITY 0x5
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
  internalUpdate(level, false);
}

void Player::internalUpdate(Level &level, bool firstUpdate) {
  
  // playerSprite.setFrame(0);

  if (wallJumpDelay) {
    wallJumpDelay--;
  }
  else {
    velX = 0;
  }
  
  if (gb.buttons.repeat(Button::right, 0) && !wallJumpDelay) {
    facingLeft = false;
    velX = velocityInPixelsPerFrame(2);
    // playerSprite.setFrame(3 + ((gb.frameCount >> 1) % 4));
  }
  if (gb.buttons.repeat(Button::left, 0) && !wallJumpDelay) {
    facingLeft = true;
    velX = velocityInPixelsPerFrame(-2);
    // playerSprite.setFrame(10 + ((gb.frameCount >> 1) % 4));
  }

  if (gb.buttons.pressed(Button::a)) {
    if (touchingGround) {
      velY = velocityInPixelsPerFrame(-6);
    }
    else if (touchingRightWall || touchingLeftWall) {
      velY = velocityInPixelsPerFrame(-6);
      wallJumpDelay = 20;
      if (touchingRightWall) {
        velX = velocityInPixelsPerFrame(-2);
      }
      else {
        velX = velocityInPixelsPerFrame(2);
      }
    }
  }
    
  touchingRightWall = touchingLeftWall = false;
  x += velX;
  if (level.collisionAt(x >> PRECISION, y >> PRECISION, getWidth(), getHeight())) {
    wallJumpDelay = 0;
    if (level.lavaAt(x >> PRECISION, y >> PRECISION, getWidth(), getHeight())) {
      resetPosition(level);
      return;
    }
    int backOne = velX > 0 ? velocityInPixelsPerFrame(-1) : velocityInPixelsPerFrame(1);
    touchingRightWall = gb.buttons.repeat(Button::right, 0) && firstUpdate && !touchingGround;
    touchingLeftWall = gb.buttons.repeat(Button::left, 0) && firstUpdate && !touchingGround;
    do {
      x += backOne;
    } 
    while(level.collisionAt(x >> PRECISION, y >> PRECISION, getWidth(), getHeight()));
  }

  velY += (touchingRightWall || touchingLeftWall) && velY > 0 ? GRAVITY >> 2 : GRAVITY;
  if (velY > 4 * ALMOST_ONE) velY = 4 * ALMOST_ONE;
  if (velY < 4 * -ALMOST_ONE) velY = 4 * -ALMOST_ONE;
  y += velY;
  if (level.collisionAt(x >> PRECISION, y >> PRECISION, getWidth(), getHeight())) {
    wallJumpDelay = 0;
    if (level.lavaAt(x >> PRECISION, y >> PRECISION, getWidth(), getHeight())) {
      resetPosition(level);
      return;
    }
    int backOne = velY > 0 ? velocityInPixelsPerFrame(-1) : velocityInPixelsPerFrame(1);
    velY = 0;
    y = y | ALMOST_ONE;
    do {
      y += backOne;
    }
    while(level.collisionAt(x >> PRECISION, y >> PRECISION, getWidth(), getHeight()));
  }

  touchingGround = level.collisionAt(x >> PRECISION, ((y  + 1) >> PRECISION), getWidth(), getHeight());
  if (touchingGround) {
    velY = 0;
  }
  else {
    if (touchingRightWall || touchingLeftWall) {
      //if (facingLeft) playerSprite.setFrame(8);
      //else playerSprite.setFrame(1);
    }
    else {
      //if (facingLeft) playerSprite.setFrame(9);
      //else playerSprite.setFrame(2);
    }
  }
}

