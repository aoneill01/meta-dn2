#include <Gamebuino-Meta.h>
#include "Game.h"
#include "GraphicsData.h"

namespace Gamebuino_Meta {
#define DMA_DESC_COUNT (3)
extern volatile uint32_t dma_desc_free_count;

static inline void wait_for_transfers_done(void) {
  while (dma_desc_free_count < DMA_DESC_COUNT);
}

static SPISettings tftSPISettings = SPISettings(24000000, MSBFIRST, SPI_MODE0);
};

uint8_t TiledDisplay::foregroundLayer[FOREGROUND_HEIGHT * FOREGROUND_WIDTH];

TiledDisplay::TiledDisplay() {
  sprites[0] = {
    0, 0, 20, 25, (uint16_t*)&characterData, false
  };
  sprites[1] = {
    SCREEN_WIDTH - 6 * 4, SCREEN_HEIGHT - 9, 5, 8, (uint16_t*)&charsData + 10 * 40, false
  };
  sprites[2] = {
    SCREEN_WIDTH - 6 * 3, SCREEN_HEIGHT - 9, 5, 8, (uint16_t*)&charsData + 0 * 40, false
  };
  sprites[3] = {
    SCREEN_WIDTH - 6 * 2, SCREEN_HEIGHT - 9, 5, 8, (uint16_t*)&charsData + 0 * 40, false
  };
  sprites[4] = {
    SCREEN_WIDTH - 6 * 1, SCREEN_HEIGHT - 9, 5, 8, (uint16_t*)&charsData + 0 * 40, false
  };
  sprites[5] = {
    1 + 0 * 6, SCREEN_HEIGHT - 9, 5, 8, (uint16_t*)&charsData + 11 * 40, false
  };
  sprites[6] = {
    1 + 1 * 6, SCREEN_HEIGHT - 9, 5, 8, (uint16_t*)&charsData + 4 * 40, false
  };
  sprites[7] = {
    1 + 2 * 6, SCREEN_HEIGHT - 9, 5, 8, (uint16_t*)&charsData + 9 * 40, false
  };
  for (int i = 8; i < 8 + 12; i++) {
    sprites[i] = {
      -5, -8, 5, 8, (uint16_t*)&charsData + 13 * 40, false
    };
  }
}

const int characterWidth = 20;
const int characterHeight = 25;

void TiledDisplay::setOffset(int offsetX, int offsetY) {
  if (offsetX < 0) offsetX = 0;  
  if (offsetY < 0) offsetY = 0;
  if (offsetX > FOREGROUND_WIDTH * 16 - SCREEN_WIDTH) offsetX = FOREGROUND_WIDTH * 16 - SCREEN_WIDTH;
  if (offsetY > FOREGROUND_HEIGHT * 16 - SCREEN_HEIGHT) offsetY = FOREGROUND_HEIGHT * 16 - SCREEN_HEIGHT;

  this->offsetX = offsetX; 
  this->offsetY = offsetY;
}

void TiledDisplay::setCharacterPosition(int characterX, int characterY) {
  sprites[0].x = characterX;
  sprites[0].y = characterY;
}

void TiledDisplay::setCharacterFrame(int frame) 
{
  sprites[0].data = (uint16_t*)&characterData + sprites[0].width * sprites[0].height * frame;
}

void TiledDisplay::setCharacterFlipped(bool flipped) {
  sprites[0].flipped = flipped;
}

void TiledDisplay::draw() {
  int tileOffset, bufferOffset;
  
  // Draw slices of the screen, each 8 pixels tall
  for (int sliceIndex = 0; sliceIndex < SCREEN_HEIGHT / SLICE_HEIGHT; sliceIndex++) {
    // 2 buffers so we can be filling the next one while the current one is being sent to the screen
    uint16_t *buffer = sliceIndex % 2 == 0 ? buffer1 : buffer2;
    // buffer = buffer1;

    // Draw the background layer, no transparency
    int yIndex = (offsetY / 2) / TILE_SIZE + sliceIndex;
    int yOffsetRemainder = (offsetY / 2) % TILE_SIZE;

    int xIndexStart = (offsetX / 2) / TILE_SIZE;
    int xOffsetRemainder = (offsetX / 2) % TILE_SIZE;

    // Partial right block
    
    tileOffset = backgroundLayer[BACKGROUND_WIDTH * (yIndex / 2) + xIndexStart / 2] * 4 * TILE_SIZE * TILE_SIZE;
    if (yIndex % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if (xIndexStart % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;

    for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
      for (int x = xOffsetRemainder; x < TILE_SIZE; x++) {
        buffer[x - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + x + y * TILE_SIZE];
      }
    }
    
    // Handle bottom half of tiles in this slice
    tileOffset = backgroundLayer[BACKGROUND_WIDTH * ((yIndex+1) / 2) + xIndexStart / 2] * 4 * TILE_SIZE * TILE_SIZE;
    if ((yIndex+1) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if (xIndexStart % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;
    
    for (int y = 0; y < yOffsetRemainder; y++) {
      for (int x = xOffsetRemainder; x < TILE_SIZE; x++) {
        buffer[x - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * SCREEN_WIDTH] = tilesData[tileOffset + x + y * TILE_SIZE];
      }
    }

    for (int xIndexOffset = 1; xIndexOffset < SCREEN_WIDTH / TILE_SIZE; xIndexOffset++) {
      tileOffset = backgroundLayer[BACKGROUND_WIDTH * (yIndex / 2) + (xIndexStart + xIndexOffset) / 2] * 4 * TILE_SIZE * TILE_SIZE;
      if (yIndex % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
      if ((xIndexStart + xIndexOffset) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;
      bufferOffset = xIndexOffset * TILE_SIZE;
      
      for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
        buffer[bufferOffset + 0 - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + 0 + y * TILE_SIZE];
        buffer[bufferOffset + 1 - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + 1 + y * TILE_SIZE];
        buffer[bufferOffset + 2 - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + 2 + y * TILE_SIZE];
        buffer[bufferOffset + 3 - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + 3 + y * TILE_SIZE];
        buffer[bufferOffset + 4 - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + 4 + y * TILE_SIZE];
        buffer[bufferOffset + 5 - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + 5 + y * TILE_SIZE];
        buffer[bufferOffset + 6 - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + 6 + y * TILE_SIZE];
        buffer[bufferOffset + 7 - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + 7 + y * TILE_SIZE];
      }

      tileOffset = backgroundLayer[BACKGROUND_WIDTH * ((yIndex + 1) / 2) + (xIndexStart + xIndexOffset) / 2] * 4 * TILE_SIZE * TILE_SIZE;
      if ((yIndex + 1) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
      if ((xIndexStart + xIndexOffset) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;
      
      for (int y = 0; y < yOffsetRemainder; y++) {
        buffer[bufferOffset + 0 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * SCREEN_WIDTH] = tilesData[tileOffset + 0 + y * TILE_SIZE];
        buffer[bufferOffset + 1 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * SCREEN_WIDTH] = tilesData[tileOffset + 1 + y * TILE_SIZE];
        buffer[bufferOffset + 2 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * SCREEN_WIDTH] = tilesData[tileOffset + 2 + y * TILE_SIZE];
        buffer[bufferOffset + 3 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * SCREEN_WIDTH] = tilesData[tileOffset + 3 + y * TILE_SIZE];
        buffer[bufferOffset + 4 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * SCREEN_WIDTH] = tilesData[tileOffset + 4 + y * TILE_SIZE];
        buffer[bufferOffset + 5 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * SCREEN_WIDTH] = tilesData[tileOffset + 5 + y * TILE_SIZE];
        buffer[bufferOffset + 6 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * SCREEN_WIDTH] = tilesData[tileOffset + 6 + y * TILE_SIZE];
        buffer[bufferOffset + 7 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * SCREEN_WIDTH] = tilesData[tileOffset + 7 + y * TILE_SIZE];
      }
    }

    // Paritial left block

    tileOffset = backgroundLayer[BACKGROUND_WIDTH * (yIndex / 2) + (xIndexStart + SCREEN_WIDTH / TILE_SIZE) / 2] * 4 * TILE_SIZE * TILE_SIZE;
    if (yIndex % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if ((xIndexStart + SCREEN_WIDTH / TILE_SIZE) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;

    for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
      for (int x = 0; x < xOffsetRemainder; x++) {
        buffer[SCREEN_WIDTH + x - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + x + y * TILE_SIZE];
      }
    }
    
    // Handle bottom half of tiles in this slice
    tileOffset = backgroundLayer[BACKGROUND_WIDTH * ((yIndex+1) / 2) + (xIndexStart + SCREEN_WIDTH / TILE_SIZE) / 2] * 4 * TILE_SIZE * TILE_SIZE;
    if ((yIndex+1) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if ((xIndexStart + SCREEN_WIDTH / TILE_SIZE) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;
    
    for (int y = 0; y < yOffsetRemainder; y++) {
      for (int x = 0; x < xOffsetRemainder; x++) {
        buffer[SCREEN_WIDTH + x - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * SCREEN_WIDTH] = tilesData[tileOffset + x + y * TILE_SIZE];
      }
    }    

    // Draw the foreground layer, with transparency
    yIndex = offsetY / TILE_SIZE + sliceIndex;
    yOffsetRemainder = offsetY % TILE_SIZE;

    xIndexStart = offsetX / TILE_SIZE;
    xOffsetRemainder = offsetX % TILE_SIZE;

    // Partial right block

    tileOffset = foregroundLayer[FOREGROUND_WIDTH * (yIndex / 2) + xIndexStart / 2] * 4 * TILE_SIZE * TILE_SIZE;
    if (yIndex % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if (xIndexStart % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;

    for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
      for (int x = xOffsetRemainder; x < TILE_SIZE; x++) {
        drawTileRow(buffer, 0, tileOffset, yOffsetRemainder, xOffsetRemainder, y, x);
      }
    }
    
    // Handle bottom half of tiles in this slice
    tileOffset = foregroundLayer[FOREGROUND_WIDTH * ((yIndex+1) / 2) + xIndexStart / 2] * 4 * TILE_SIZE * TILE_SIZE;
    if ((yIndex+1) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if (xIndexStart % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;
    
    for (int y = 0; y < yOffsetRemainder; y++) {
      for (int x = xOffsetRemainder; x < TILE_SIZE; x++) {
        drawTileRow(buffer, 0, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, x);
      }
    }      
    
    for (int xIndexOffset = 1; xIndexOffset < SCREEN_WIDTH / TILE_SIZE; xIndexOffset++) {
      // Handle top half of tiles in this slice
      tileOffset = foregroundLayer[FOREGROUND_WIDTH * (yIndex / 2) + (xIndexStart + xIndexOffset) / 2] * 4 * TILE_SIZE * TILE_SIZE;
      if (yIndex % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
      if ((xIndexStart + xIndexOffset) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;
      
      bufferOffset = xIndexOffset * TILE_SIZE;

      for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder, xOffsetRemainder, y, 0);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder, xOffsetRemainder, y, 1);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder, xOffsetRemainder, y, 2);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder, xOffsetRemainder, y, 3);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder, xOffsetRemainder, y, 4);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder, xOffsetRemainder, y, 5);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder, xOffsetRemainder, y, 6);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder, xOffsetRemainder, y, 7);
      }
      
      // Handle bottom half of tiles in this slice
      tileOffset = foregroundLayer[FOREGROUND_WIDTH * ((yIndex+1) / 2) + (xIndexStart + xIndexOffset) / 2] * 4 * TILE_SIZE * TILE_SIZE;
      if ((yIndex+1) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
      if ((xIndexStart + xIndexOffset) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;
      
      for (int y = 0; y < yOffsetRemainder; y++) {
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, 0);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, 1);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, 2);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, 3);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, 4);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, 5);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, 6);
        drawTileRow(buffer, bufferOffset, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, 7);
      }      
    }

    // Paritial left block

    tileOffset = foregroundLayer[FOREGROUND_WIDTH * (yIndex / 2) + (xIndexStart + SCREEN_WIDTH / TILE_SIZE) / 2] * 4 * TILE_SIZE * TILE_SIZE;
    if (yIndex % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if ((xIndexStart + SCREEN_WIDTH / TILE_SIZE) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;

    for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
      for (int x = 0; x < xOffsetRemainder; x++) {
        drawTileRow(buffer, SCREEN_WIDTH, tileOffset, yOffsetRemainder, xOffsetRemainder, y, x);
      }
    }
    
    // Handle bottom half of tiles in this slice
    tileOffset = foregroundLayer[FOREGROUND_WIDTH * ((yIndex+1) / 2) + (xIndexStart + SCREEN_WIDTH / TILE_SIZE) / 2] * 4 * TILE_SIZE * TILE_SIZE;
    if ((yIndex+1) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if ((xIndexStart + SCREEN_WIDTH / TILE_SIZE) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;
    
    for (int y = 0; y < yOffsetRemainder; y++) {
      for (int x = 0; x < xOffsetRemainder; x++) {
        drawTileRow(buffer, SCREEN_WIDTH, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, x);
      }
    }

    // Draw sprites

    int sliceY = sliceIndex * SLICE_HEIGHT;
    
    for (int i = 0; i < 20; i++) {
      if ((sliceY <= sprites[i].y + sprites[i].height) && (sliceY + SLICE_HEIGHT > sprites[i].y)) {
        int startIndex = (sprites[i].y <= sliceY) ? 0 : sprites[i].y - sliceY;
        int endIndex = sprites[i].y + sprites[i].height >= sliceY + SLICE_HEIGHT ? 7 : sprites[i].y + sprites[i].height - sliceY - 1;
        for (int y = startIndex; y <= endIndex; y++) {
          
          for (int x = sprites[i].x < 0 ? 0 : sprites[i].x; x < sprites[i].x + sprites[i].width && x < SCREEN_WIDTH; x++) {
            int value;
            if (sprites[i].flipped) {
              value = sprites[i].data[(sliceY - sprites[i].y + y) * sprites[i].width + sprites[i].width - (x - sprites[i].x) - 1];
            }
            else {
              value = sprites[i].data[(sliceY - sprites[i].y + y) * sprites[i].width - sprites[i].x + x];
            }
            if (value != 0xE007) {
              buffer[x + y * SCREEN_WIDTH] = value;
            }
          }
        }
      }
    }

    waitForPreviousDraw();
    customDrawBuffer(0, sliceY, buffer, SCREEN_WIDTH, SLICE_HEIGHT);
  }
  
  waitForPreviousDraw();
}

inline void TiledDisplay::drawTileRow(uint16_t *buffer, const int bufferOffset, const int tileOffset, const int yOffsetRemainder, const int xOffsetRemainder, const int y, const int x) {
  if ((tilesData[tileOffset + x + y * TILE_SIZE]) != 0xE007) {
    buffer[bufferOffset + x - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + x + y * TILE_SIZE];
  }
}

void TiledDisplay::customDrawBuffer(int16_t x, int16_t y, uint16_t *buffer, uint16_t w, uint16_t h) {
  if (pixelMask != 0xffff) {
    for (int i = 0; i < w * h; i++) {
      buffer[i] = pixelMask & buffer[i];
    }
  }
  drawPending = true;
  gb.tft.setAddrWindow(x, y, x + w - 1, y + h - 1);
  SPI.beginTransaction(Gamebuino_Meta::tftSPISettings);
  gb.tft.dataMode();
  gb.tft.sendBuffer(buffer, w*h);

#ifdef SCREEN_RECORD
  while (SerialUSB.read() == -1);
  SerialUSB.print("start");
  SerialUSB.write(x);
  SerialUSB.write(y);
  SerialUSB.write(w);
  SerialUSB.write(h);
  SerialUSB.write((const char*)buffer, 2*w*h);
#endif
}

void TiledDisplay::waitForPreviousDraw() {
  if (drawPending) {
    Gamebuino_Meta::wait_for_transfers_done();
    gb.tft.idleMode();
    SPI.endTransaction();
    drawPending = false;
  }
}
