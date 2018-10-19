#pragma once

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128

#define TILE_SIZE 8
#define SLICE_HEIGHT 8

#define FOREGROUND_WIDTH 64
#define FOREGROUND_HEIGHT 80

#define BACKGROUND_WIDTH 37
#define BACKGROUND_HEIGHT 44

class TiledDisplay {
  inline void drawTileRow(uint16_t *buffer, const int bufferOffset, const int tileOffset, const int yOffsetRemainder, const int xOffsetRemainder, const int y, const int x) __attribute__((always_inline));
  void customDrawBuffer(int16_t x, int16_t y, uint16_t *buffer, uint16_t w, uint16_t h);
  void waitForPreviousDraw();
  bool drawPending = false;
  int characterX, characterY;
  int animationOffset;
  uint16_t buffer1[SCREEN_WIDTH * 8];
  uint16_t buffer2[SCREEN_WIDTH * 8];  
  const static uint8_t backgroundLayer[BACKGROUND_WIDTH * BACKGROUND_HEIGHT];
  const static uint16_t sample_tilesData[];
  const static uint16_t characterData[];
  
public:
  void draw();
  void setOffset(int offsetX, int offsetY);
  void setCharacterPosition(int characterX, int characterY);
  void setCharacterFrame(int frame);

  int offsetX, offsetY;
  bool characterFlipped = false;
  uint16_t pixelMask = 0xffff;
  static uint8_t foregroundLayer[FOREGROUND_HEIGHT * FOREGROUND_WIDTH];
};
