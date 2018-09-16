#pragma once
#define FIXED_POINTS_NO_RANDOM
#include <FixedPoints.h>
#include <FixedPointsCommon.h>
#include "Level.h"

enum class PlayerState { Idle, Run, Wall, Jump, Fall, Dead };

class Player {
  SQ15x16 x, y;
  SQ15x16 velX, velY;
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
  bool isDead();
  
  int getWidth() { return 14; }
  int getHeight() { return 23; }
};
