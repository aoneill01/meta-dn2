#pragma once

#define LEVEL_ROWS 80
#define LEVEL_COLS 64 

class Level {
  int levelIndex = -1;
  const static uint8_t tiles[LEVEL_ROWS][LEVEL_COLS];

  byte tileAt(int x, int y);
public:
  bool collisionAt(int x, int y, int width, int height);
  bool damageAt(int x, int y, int width, int height);
};
