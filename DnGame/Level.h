#pragma once
#include "TiledDisplay.h"
#include "TileSet.h"

#define LEVEL_ROWS 80
#define LEVEL_COLS 64 

class Level {
  TiledDisplay *tiledDisplay;
  int levelIndex = -1;
  uint8_t *tiles;

  byte tileAt(int x, int y);
public:
  Level(TiledDisplay *tiledDisplay);
  const static uint8_t typeMap[128];

  bool collisionsAt(int x, int y, int width, int height, TileSet& result);
  void setTile(int x, int y, uint8_t tile);
  uint8_t getTile(int x, int y);
};
