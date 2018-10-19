#pragma once

#include "Player.h"
#include "Level.h"
#include "TiledDisplay.h"
#include "BreakableTiles.h"
#include "DisappearingTiles.h"

class Game {
  Player player;
  TiledDisplay tiledDisplay;
  Level level;
  BreakableTiles breakableTiles;
  DisappearingTiles disappearingTiles;
  
public:
  Game() : level(&tiledDisplay) {}
  void loadLevel();
  void reset();  
  void handleTick();
};
