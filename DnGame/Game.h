#pragma once

#include "Player.h"
#include "Level.h"
#include "TiledDisplay.h"

class Game {
  Level level;
  Player player;
  TiledDisplay tiledDisplay;
  BreakableBlocks breakableBlocks;
  
public: 
  void reset();
  void handleTick();
};
