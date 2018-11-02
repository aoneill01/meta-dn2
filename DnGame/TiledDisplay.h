#pragma once

#include "Constants.h"

struct Sprite {
    int x, y, width, height;
    uint16_t *data;
    bool flipped;
};

class TiledDisplay {
  inline void drawTileRow(uint16_t *buffer, const int bufferOffset, const int tileOffset, const int yOffsetRemainder, const int xOffsetRemainder, const int y, const int x) __attribute__((always_inline));
  void customDrawBuffer(int16_t x, int16_t y, uint16_t *buffer, uint16_t w, uint16_t h);
  void waitForPreviousDraw();
  bool drawPending = false;
  uint16_t buffer1[SCREEN_WIDTH * 8];
  uint16_t buffer2[SCREEN_WIDTH * 8];
  
public:
  TiledDisplay();
  void draw();
  void setOffset(int offsetX, int offsetY);
  void setCharacterPosition(int characterX, int characterY);
  void setCharacterFrame(int frame);
  void setCharacterFlipped(bool flipped);

  int offsetX, offsetY;
  uint16_t pixelMask = 0xffff;
  Sprite sprites[8];
  static uint8_t foregroundLayer[FOREGROUND_HEIGHT * FOREGROUND_WIDTH];
};
