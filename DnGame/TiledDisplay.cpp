// #define SCREEN_RECORD true

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

uint8_t TiledDisplay::foregroundLayer[FOREGROUND_HEIGHT * FOREGROUND_WIDTH] = 
{66,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,82,17,66,17,17,17,17,17,17,17,17,17,17,22,25,25,20,82,17,17,17,66,17,17,17,17,17,17,17,17,17,17,17,17,82,17,17,17,17,17,66,17,17,17,17,17,17,17,17,17,64,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,65,17,17,22,25,25,20,17,17,17,17,17,17,17,17,64,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,65,17,17,17,17,17,17,64,37,38,25,25,25,72,41,41,41,41,41,41,41,41,41,41,41,41,41,41,73,25,25,25,90,36,37,65,22,25,25,20,17,17,17,17,17,17,64,37,38,41,41,41,73,25,25,25,25,25,25,25,25,25,25,25,36,37,37,37,65,17,64,38,25,25,72,41,41,42,21,21,21,21,21,21,21,21,21,21,21,21,21,21,40,41,73,25,25,25,25,36,38,25,25,36,37,65,17,17,17,64,34,21,21,21,21,21,40,41,41,41,41,73,74,25,25,25,90,25,25,25,25,25,36,65,22,90,72,41,42,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,40,73,25,25,25,25,25,25,25,25,25,20,17,17,17,18,21,21,21,21,21,21,21,21,21,21,21,40,73,25,72,41,41,41,41,41,73,25,25,20,22,25,26,21,21,21,21,106,126,21,21,108,105,21,21,21,21,21,21,21,21,21,21,21,21,40,41,41,41,73,25,90,25,25,25,36,65,17,64,34,21,21,21,21,21,21,21,21,21,21,21,21,24,25,26,21,21,21,21,21,40,73,25,20,22,25,26,21,21,21,21,127,67,68,68,69,111,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,40,41,73,25,25,25,25,20,17,18,21,21,21,21,21,21,21,67,0,5,5,5,5,6,25,26,21,21,21,21,21,21,24,25,20,80,6,26,21,21,21,21,21,84,64,65,100,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,40,73,25,25,25,20,17,18,10,21,21,21,21,21,21,84,81,17,17,17,101,38,73,88,10,21,21,21,21,21,24,25,20,17,22,26,21,21,21,21,21,84,80,81,100,21,51,21,21,21,21,8,9,10,21,21,21,21,21,21,21,21,21,21,21,24,25,25,25,20,17,18,88,10,21,21,21,21,21,115,116,116,116,116,117,21,24,25,88,9,10,21,21,21,24,4,81,17,22,26,21,21,21,21,21,115,116,116,117,21,21,21,8,9,9,89,25,26,21,21,21,21,21,21,21,21,21,21,21,24,25,25,25,20,17,18,25,88,10,21,21,21,21,21,21,21,21,21,21,21,40,41,73,55,26,21,21,21,24,20,17,17,80,6,21,21,21,21,21,21,21,21,21,8,9,9,89,72,41,41,41,42,21,21,21,21,21,21,21,21,21,21,21,24,25,74,25,20,17,18,25,25,88,10,21,21,21,21,21,21,21,21,21,21,21,21,24,72,42,21,21,8,89,20,17,17,17,80,2,21,21,8,9,9,9,9,9,89,25,55,72,42,21,21,21,21,21,21,21,21,21,21,21,21,8,9,9,89,25,25,25,20,64,34,25,90,25,88,9,10,21,21,21,21,21,21,21,21,21,21,24,26,21,21,21,24,4,81,17,17,17,17,80,2,9,89,25,72,41,41,41,41,41,41,42,21,97,97,97,97,97,97,97,97,21,0,1,1,6,25,25,25,25,25,25,20,18,74,25,25,25,25,25,88,10,21,21,21,21,21,21,21,21,21,24,26,21,21,8,89,20,17,17,17,17,17,17,18,25,25,74,42,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,70,71,80,5,5,5,5,5,5,81,18,41,41,41,73,25,25,90,26,21,21,21,21,21,21,21,21,8,89,88,9,9,89,4,81,17,17,17,17,17,17,80,1,1,1,2,21,21,21,67,68,68,68,68,69,21,21,21,21,21,21,21,21,16,86,87,82,17,17,17,17,17,17,17,34,21,21,21,40,41,41,41,42,21,21,21,21,8,9,9,9,89,4,5,5,5,5,81,17,17,82,17,17,17,17,17,17,17,17,18,21,21,21,0,81,17,17,80,2,68,68,68,68,69,21,21,8,36,37,65,17,17,17,66,17,17,17,17,100,21,21,21,21,21,21,21,21,21,21,8,9,89,52,53,54,25,36,37,37,37,37,37,37,65,17,17,17,17,17,17,17,17,17,18,21,21,21,16,17,17,17,17,17,17,17,17,80,6,9,9,89,25,25,32,37,37,37,37,37,99,17,17,100,21,21,21,21,21,21,21,21,21,21,40,41,41,73,25,25,25,90,25,72,41,41,41,73,36,65,82,17,17,17,17,17,17,17,18,21,21,21,16,17,17,17,66,82,17,80,81,17,80,6,25,25,25,72,41,41,73,25,88,10,115,116,116,117,21,21,21,21,21,21,21,21,21,21,21,21,21,40,41,73,74,25,25,26,21,21,21,40,73,20,17,17,17,17,17,17,17,17,18,21,21,21,16,82,17,17,17,17,17,17,17,17,17,80,6,74,25,26,21,21,40,41,73,26,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,24,25,25,25,88,9,10,21,21,40,20,66,17,17,17,17,17,17,17,18,21,21,21,16,17,17,17,17,17,17,66,17,17,17,17,80,6,90,26,21,21,21,21,24,88,9,9,9,9,9,10,21,21,0,2,21,21,21,21,0,5,5,5,5,5,5,5,5,5,6,26,21,21,21,20,17,17,17,17,17,17,17,17,18,21,21,21,16,17,17,17,17,17,17,17,17,17,82,17,17,80,6,88,9,9,9,9,89,25,25,25,90,25,25,88,10,21,16,80,68,68,68,68,81,66,17,17,17,80,81,17,82,17,22,88,10,21,21,20,17,82,17,66,17,17,17,17,18,21,21,21,16,17,17,17,17,17,82,17,17,17,66,17,17,17,80,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,81,17,17,80,81,17,17,17,17,17,82,17,17,17,17,17,22,25,26,21,21,20,17,17,17,64,65,17,17,17,18,21,21,21,16,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,81,17,17,17,66,17,17,17,17,17,17,17,17,17,17,17,17,17,64,65,17,17,17,17,17,22,25,88,10,21,20,17,17,64,34,116,116,116,116,116,21,21,21,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,32,33,33,33,65,17,22,25,25,88,9,20,17,64,34,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,82,22,25,25,25,25,20,64,34,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,22,90,25,25,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,75,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,22,25,25,25,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,91,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,20,17,22,25,25,25,90,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,91,21,21,21,21,21,21,97,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,22,25,25,74,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,75,21,21,21,21,21,21,21,91,21,21,21,21,21,21,21,21,21,21,21,21,21,21,97,21,21,21,21,21,21,21,21,21,21,16,17,22,72,41,73,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,108,110,21,21,91,21,21,21,21,21,97,21,91,21,108,109,109,109,110,21,21,21,97,21,21,21,21,21,21,21,21,21,21,97,21,21,21,21,16,17,22,26,21,24,25,20,18,21,21,21,21,21,21,21,21,97,97,97,21,21,21,21,21,21,21,21,21,21,91,21,108,109,105,21,21,21,127,21,21,21,21,21,21,21,21,21,21,21,21,97,21,21,21,21,97,21,21,21,21,21,21,21,16,17,22,26,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,124,125,126,21,21,21,21,21,21,127,21,21,21,111,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,22,26,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,22,26,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,21,21,21,21,21,16,17,22,26,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,32,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,34,21,21,21,21,21,16,17,22,26,21,24,74,20,18,21,21,21,21,21,21,21,21,51,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,32,65,22,26,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,22,88,9,89,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,22,25,72,41,73,20,18,21,21,21,21,51,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,22,25,26,21,24,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,22,25,26,21,24,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,22,25,26,21,24,20,18,21,51,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,0,81,22,25,26,21,24,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,32,65,22,25,26,21,24,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,22,25,26,21,24,20,18,21,48,49,49,49,50,21,21,21,21,48,49,49,49,49,50,21,21,21,21,48,49,49,49,50,21,21,21,21,48,49,49,50,21,21,21,21,48,49,50,21,21,21,21,48,49,50,21,0,5,5,2,21,21,21,21,16,22,25,26,21,24,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,66,64,34,21,21,21,21,16,22,25,26,21,24,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,82,18,21,21,21,21,21,16,22,25,88,9,89,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,0,81,17,18,21,21,21,21,0,81,22,25,25,25,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,22,21,21,21,21,32,65,22,90,25,25,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,18,21,21,21,21,21,16,22,25,25,72,41,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,0,81,17,17,80,2,21,21,21,21,16,22,25,25,26,21,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,17,64,34,21,21,21,21,16,22,74,25,26,21,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,17,18,21,21,21,21,21,16,22,25,90,26,21,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,0,81,17,17,17,18,21,21,21,21,0,81,22,25,25,26,21,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,17,17,22,21,21,21,21,32,65,22,41,73,26,21,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,82,17,17,18,21,21,21,21,21,16,22,21,24,26,21,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,0,81,17,17,17,17,80,2,21,21,21,21,16,22,21,24,26,21,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,17,66,17,64,34,21,21,21,21,16,22,21,24,26,21,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,17,17,17,18,21,21,21,21,21,16,22,21,24,26,21,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,0,81,17,17,17,82,17,18,21,21,21,21,0,81,22,21,24,26,21,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,82,17,17,17,17,17,18,21,21,21,21,32,65,22,21,24,88,9,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,17,17,17,17,18,21,21,21,21,21,16,22,21,40,73,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,0,81,17,17,66,17,17,17,80,2,21,21,21,21,16,22,21,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,17,17,17,17,82,64,34,21,21,21,21,16,22,21,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,82,17,17,17,66,18,21,21,21,21,21,16,22,21,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,0,81,17,17,17,17,17,17,17,18,21,21,21,21,0,81,22,21,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,17,17,17,17,17,17,18,21,21,21,21,32,65,22,10,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,66,17,17,17,17,17,18,21,21,21,21,21,16,22,26,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,0,81,17,17,17,17,82,17,17,17,80,2,21,21,21,21,16,22,26,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,82,17,17,17,17,66,17,17,64,34,21,21,21,21,16,22,26,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,17,17,17,17,17,17,17,18,21,21,21,21,21,16,22,26,21,24,25,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,0,81,17,17,17,17,17,17,17,17,17,18,21,21,21,21,0,81,22,26,21,40,73,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,66,17,17,17,17,82,17,17,18,21,21,21,21,32,37,38,26,21,21,24,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,17,82,17,17,17,17,17,17,18,21,21,21,21,21,40,41,42,21,21,24,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,0,81,17,17,17,17,17,66,17,17,17,17,80,2,21,21,21,21,21,21,21,21,21,24,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,17,17,17,17,17,17,17,17,17,17,18,21,21,21,21,21,21,21,21,21,24,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,16,17,17,17,17,17,17,17,17,17,66,17,17,22,9,9,9,9,9,9,10,21,21,24,20,18,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,0,81,17,66,17,17,17,82,17,17,17,17,17,17,80,5,5,5,5,5,6,88,9,9,89,20,80,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,21,21,4,5,81,17,17,82,17,17,17,17,17,17,17,17,17,17,66,17,17,17,17,17,80,5,5,5,5,81};

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
      -5, -8, 5, 8, (uint16_t*)&charsData + 13 * 40, i % 2 == 0
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
  int additionalOffset = gb.buttons.repeat(Button::a, 0) ? 32768 : 0;
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
    
    tileOffset = backgroundLayer[BACKGROUND_WIDTH * (yIndex / 2) + xIndexStart / 2] * 4 * TILE_SIZE * TILE_SIZE + additionalOffset;
    if (tileOffset - additionalOffset > 32768) {
      if (gb.buttons.repeat(Button::a, 0)) tileOffset = 5376;
      else tileOffset -= 32768;
    }
    if (yIndex % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if (xIndexStart % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;

    for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
      for (int x = xOffsetRemainder; x < TILE_SIZE; x++) {
        buffer[x - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + x + y * TILE_SIZE];
      }
    }
    
    // Handle bottom half of tiles in this slice
    tileOffset = backgroundLayer[BACKGROUND_WIDTH * ((yIndex+1) / 2) + xIndexStart / 2] * 4 * TILE_SIZE * TILE_SIZE + additionalOffset;
    if (tileOffset - additionalOffset > 32768) {
      if (gb.buttons.repeat(Button::a, 0)) tileOffset = 5376;
      else tileOffset -= 32768;
    }
    if ((yIndex+1) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if (xIndexStart % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;
    
    for (int y = 0; y < yOffsetRemainder; y++) {
      for (int x = xOffsetRemainder; x < TILE_SIZE; x++) {
        buffer[x - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * SCREEN_WIDTH] = tilesData[tileOffset + x + y * TILE_SIZE];
      }
    }

    for (int xIndexOffset = 1; xIndexOffset < SCREEN_WIDTH / TILE_SIZE; xIndexOffset++) {
      tileOffset = backgroundLayer[BACKGROUND_WIDTH * (yIndex / 2) + (xIndexStart + xIndexOffset) / 2] * 4 * TILE_SIZE * TILE_SIZE + additionalOffset;
      if (tileOffset - additionalOffset > 32768) {
        if (gb.buttons.repeat(Button::a, 0)) tileOffset = 5376;
        else tileOffset -= 32768;
      }
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

      tileOffset = backgroundLayer[BACKGROUND_WIDTH * ((yIndex + 1) / 2) + (xIndexStart + xIndexOffset) / 2] * 4 * TILE_SIZE * TILE_SIZE + additionalOffset;
      if (tileOffset - additionalOffset > 32768) {
        if (gb.buttons.repeat(Button::a, 0)) tileOffset = 5376;
        else tileOffset -= 32768;
      }
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

    tileOffset = backgroundLayer[BACKGROUND_WIDTH * (yIndex / 2) + (xIndexStart + SCREEN_WIDTH / TILE_SIZE) / 2] * 4 * TILE_SIZE * TILE_SIZE + additionalOffset;
    if (tileOffset - additionalOffset > 32768) {
      if (gb.buttons.repeat(Button::a, 0)) tileOffset = 5376;
      else tileOffset -= 32768;
    }
    if (yIndex % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if ((xIndexStart + SCREEN_WIDTH / TILE_SIZE) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;

    for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
      for (int x = 0; x < xOffsetRemainder; x++) {
        buffer[SCREEN_WIDTH + x - xOffsetRemainder + (y - yOffsetRemainder) * SCREEN_WIDTH] = tilesData[tileOffset + x + y * TILE_SIZE];
      }
    }
    
    // Handle bottom half of tiles in this slice
    tileOffset = backgroundLayer[BACKGROUND_WIDTH * ((yIndex+1) / 2) + (xIndexStart + SCREEN_WIDTH / TILE_SIZE) / 2] * 4 * TILE_SIZE * TILE_SIZE + additionalOffset;
    if (tileOffset - additionalOffset > 32768) {
      if (gb.buttons.repeat(Button::a, 0)) tileOffset = 5376;
      else tileOffset -= 32768;
    }
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

    tileOffset = foregroundLayer[FOREGROUND_WIDTH * (yIndex / 2) + xIndexStart / 2] * 4 * TILE_SIZE * TILE_SIZE + additionalOffset;
    if (tileOffset - additionalOffset > 32768) {
      if (gb.buttons.repeat(Button::a, 0)) tileOffset = 5376;
      else tileOffset -= 32768;
    }
    if (yIndex % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if (xIndexStart % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;

    for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
      for (int x = xOffsetRemainder; x < TILE_SIZE; x++) {
        drawTileRow(buffer, 0, tileOffset, yOffsetRemainder, xOffsetRemainder, y, x);
      }
    }
    
    // Handle bottom half of tiles in this slice
    tileOffset = foregroundLayer[FOREGROUND_WIDTH * ((yIndex+1) / 2) + xIndexStart / 2] * 4 * TILE_SIZE * TILE_SIZE + additionalOffset;
    if (tileOffset - additionalOffset > 32768) {
      if (gb.buttons.repeat(Button::a, 0)) tileOffset = 5376;
      else tileOffset -= 32768;
    }
    if ((yIndex+1) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if (xIndexStart % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;
    
    for (int y = 0; y < yOffsetRemainder; y++) {
      for (int x = xOffsetRemainder; x < TILE_SIZE; x++) {
        drawTileRow(buffer, 0, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, x);
      }
    }      
    
    for (int xIndexOffset = 1; xIndexOffset < SCREEN_WIDTH / TILE_SIZE; xIndexOffset++) {
      // Handle top half of tiles in this slice
      tileOffset = foregroundLayer[FOREGROUND_WIDTH * (yIndex / 2) + (xIndexStart + xIndexOffset) / 2] * 4 * TILE_SIZE * TILE_SIZE + additionalOffset;
      if (tileOffset - additionalOffset > 32768) {
        if (gb.buttons.repeat(Button::a, 0)) tileOffset = 5376;
        else tileOffset -= 32768;
      }
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
      tileOffset = foregroundLayer[FOREGROUND_WIDTH * ((yIndex+1) / 2) + (xIndexStart + xIndexOffset) / 2] * 4 * TILE_SIZE * TILE_SIZE + additionalOffset;
      if (tileOffset - additionalOffset > 32768) {
        if (gb.buttons.repeat(Button::a, 0)) tileOffset = 5376;
        else tileOffset -= 32768;
      }
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

    tileOffset = foregroundLayer[FOREGROUND_WIDTH * (yIndex / 2) + (xIndexStart + SCREEN_WIDTH / TILE_SIZE) / 2] * 4 * TILE_SIZE * TILE_SIZE + additionalOffset;
    if (tileOffset - additionalOffset > 32768) {
      if (gb.buttons.repeat(Button::a, 0)) tileOffset = 5376;
      else tileOffset -= 32768;
    }
    if (yIndex % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE * 2;
    if ((xIndexStart + SCREEN_WIDTH / TILE_SIZE) % 2 == 1) tileOffset += TILE_SIZE * TILE_SIZE;

    for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
      for (int x = 0; x < xOffsetRemainder; x++) {
        drawTileRow(buffer, SCREEN_WIDTH, tileOffset, yOffsetRemainder, xOffsetRemainder, y, x);
      }
    }
    
    // Handle bottom half of tiles in this slice
    tileOffset = foregroundLayer[FOREGROUND_WIDTH * ((yIndex+1) / 2) + (xIndexStart + SCREEN_WIDTH / TILE_SIZE) / 2] * 4 * TILE_SIZE * TILE_SIZE + additionalOffset;
    if (tileOffset - additionalOffset > 32768) {
      if (gb.buttons.repeat(Button::a, 0)) tileOffset = 5376;
      else tileOffset -= 32768;
    }
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
