#pragma once

#include "Level.h"

enum class PlayerState { Idle, Run, Wall, Jump, Fall };

class Player {
  int x, y;
  int velX, velY;
  int wallJumpDelay;
  PlayerState state;
  int sameStateCount;
  bool touchingGround, touchingRightWall, touchingLeftWall;

  PlayerState internalUpdate(Level &l, bool firstUpdate);
public:
  bool facingLeft;
  int animationFrame;
  void resetPosition(Level &l);
  int getX(); 
  int getY(); 
  void update(Level &l);
  
  int getWidth() { return 14; }
  int getHeight() { return 23; }
};

