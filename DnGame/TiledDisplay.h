#pragma once

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128

#define TILE_SIZE 8
#define SLICE_HEIGHT 8

#define FOREGROUND_WIDTH 64
#define FOREGROUND_HEIGHT 80

#define BACKGROUND_WIDTH 37
#define BACKGROUND_HEIGHT 44

#define EMPTY_TILE 21
#define BREAK1_TILE 98
#define BREAK2_TILE 113
#define BREAK3_TILE 114

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
  int animationOffset;
  uint16_t buffer1[SCREEN_WIDTH * 8];
  uint16_t buffer2[SCREEN_WIDTH * 8];  
  const static uint8_t backgroundLayer[BACKGROUND_WIDTH * BACKGROUND_HEIGHT];
  const static uint16_t sample_tilesData[];
  const static uint16_t characterData[];
  
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
  const static uint16_t charsData[];
};
