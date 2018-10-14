#pragma once

#include "TileSet.h"

#define LEVEL_ROWS 80
#define LEVEL_COLS 64 

class Level {
  int levelIndex = -1;
  uint8_t *tiles;

  byte tileAt(int x, int y);
public:
  const static uint8_t typeMap[128];

  bool collisionsAt(int x, int y, int width, int height, TileSet& result);
  void clearTile(int x, int y);
};
