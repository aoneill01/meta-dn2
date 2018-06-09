#pragma once

#define W 160
#define H 128

#define TILE_SIZE 8
#define SLICE_HEIGHT 8

#define LAYER_WIDTH 64
#define LAYER_HEIGHT 80

class TiledDisplay {
  inline void drawTileRow(uint16_t *buffer, const int bufferOffset, const int tileOffset, const int yOffsetRemainder, const int xOffsetRemainder, const int y, const int x) __attribute__((always_inline));
  void customDrawBuffer(int16_t x, int16_t y, uint16_t *buffer, uint16_t w, uint16_t h);
  void waitForPreviousDraw();
  bool drawPending = false;
  int characterX, characterY;
  int animationOffset;
  uint16_t buffer1[W * 8];
  uint16_t buffer2[W * 8];
  const static uint8_t layer1[LAYER_HEIGHT][LAYER_WIDTH];
  const static uint8_t layer2[44][37]; // TODO Fix magic values
  const static uint16_t sample_tilesData[];
  const static uint16_t characterData[];
  
public:
  void draw();
  void setOffset(int offsetX, int offsetY);
  void setCharacterPosition(int characterX, int characterY) { this->characterX = characterX, this->characterY = characterY; }
  void setCharacterFrame(int frame);

  int offsetX, offsetY;
  bool characterFlipped = false;
};
