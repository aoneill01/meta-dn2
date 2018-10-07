#pragma once

#include "TileSet.h"

#define LEVEL_ROWS 80
#define LEVEL_COLS 64 

class Level {
  int levelIndex = -1;
  //const static uint8_t oldTiles[LEVEL_ROWS][LEVEL_COLS];
  const static uint8_t typeMap[128];
  uint8_t *tiles;

  byte tileAt(int x, int y);
public:
  bool collisionsAt(int x, int y, int width, int height, TileSet& result);
  void clearTile(int x, int y);
};
