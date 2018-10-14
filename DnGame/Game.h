#pragma once

#include "Player.h"
#include "Level.h"
#include "TiledDisplay.h"
#include "BreakableTiles.h"
#include "DisappearingTiles.h"

class Game {
  Level level;
  Player player;
  TiledDisplay tiledDisplay;
  BreakableTiles breakableTiles;
  DisappearingTiles disappearingTiles;
  
public: 
  void loadLevel();
  void reset();  
  void handleTick();
};
