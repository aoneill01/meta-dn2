#pragma once

#include "Level.h"

class Player {
  int x, y;
  int velX, velY;
  int wallJumpDelay;
  bool touchingGround, facingLeft, touchingRightWall, touchingLeftWall;

  void internalUpdate(Level &l, bool firstUpdate);
public:
  int animationFrame;
  void resetPosition(Level &l);
  int getX(); 
  int getY(); 
  void update(Level &l);
  
  int getWidth() { return 14; }
  int getHeight() { return 23; }
};

