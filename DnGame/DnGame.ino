#include <Gamebuino-Meta.h>

#define W 160
#define H 128

#define TILE_SIZE 8
#define SLICE_HEIGHT 8

#define LAYER_WIDTH 30
#define LAYER_HEIGHT 20
uint8_t layer1[LAYER_HEIGHT][LAYER_WIDTH] = {
  {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  1,  5,  6,  7,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  2, 13, 13, 13,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  3, 13, 12, 13, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  4, 13, 13, 13, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  2, 13, 13, 13,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  3, 13, 13, 13, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  4, 13, 13, 13, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  2, 13, 13, 13,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  3, 13, 13, 13, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  4, 13, 13, 13, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  2, 13, 13, 13,  9,  0,  0,  0,  0,  0,  0,  0,  1,  5,  6,  7,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  3, 13, 13, 13, 10,  0,  0,  0,  0,  0,  0,  0,  2, 13, 13, 13,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  4, 13, 13, 13, 11,  0,  0,  0,  0,  0,  0,  0,  3, 13, 13, 13, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  2, 13, 13, 13,  9,  0,  0,  0,  0,  0,  0,  0,  4, 13, 13, 13, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  3, 13, 13, 13, 10,  0,  0,  0,  0,  0,  0,  0,  2, 13, 13, 12,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  4, 13, 13, 13, 11,  0,  0,  0,  0,  0,  0,  0,  3, 13, 13, 13, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  2, 13, 13, 13,  9,  0,  0,  1,  5,  6,  7,  5,  6,  7,  5,  6,  7,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  3, 13, 13, 13, 10,  0,  0,  2, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  4, 12, 13, 13, 11,  0,  0,  3, 13, 13, 13, 13, 13, 13, 13, 13, 13, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
  
};

uint8_t layer2[20][30] = {
  { 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29 },
  { 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29 },
  { 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29 },
  { 29, 29, 14, 18, 19, 20, 21, 22, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29 },
  { 29, 29, 15, 28, 28, 28, 28, 23, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29 },
  { 29, 29, 16, 28, 28, 27, 28, 24, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29 },
  { 29, 29, 17, 28, 28, 28, 28, 25, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29 },
  { 29, 29, 15, 28, 28, 28, 28, 23, 14, 18, 19, 20, 21, 18, 19, 20, 21, 18, 19, 20, 21, 18, 19, 20, 21, 18, 19, 20, 22, 29 },
  { 29, 29, 16, 28, 26, 28, 28, 24, 15, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 23, 29 },
  { 29, 29, 17, 28, 28, 28, 28, 25, 16, 28, 28, 28, 28, 28, 28, 28, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 24, 29 },
  { 29, 29, 15, 28, 28, 28, 28, 23, 17, 28, 28, 28, 26, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 25, 29 },
  { 29, 29, 16, 28, 28, 28, 28, 24, 15, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 23, 29 },
  { 29, 29, 17, 28, 28, 28, 28, 25, 16, 28, 28, 28, 28, 28, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 24, 29 },
  { 29, 29, 15, 28, 28, 28, 26, 23, 17, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 25, 29 },
  { 29, 29, 16, 28, 28, 28, 28, 24, 15, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 23, 29 },
  { 29, 29, 17, 28, 28, 28, 28, 25, 16, 28, 28, 28, 28, 28, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 24, 29 },
  { 29, 29, 15, 28, 28, 28, 26, 23, 17, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 25, 29 },
  { 29, 29, 16, 28, 28, 28, 28, 24, 15, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 23, 29 },
  { 29, 29, 17, 28, 28, 28, 28, 25, 16, 28, 28, 28, 28, 28, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 24, 29 },
  { 29, 29, 15, 28, 28, 28, 26, 23, 17, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 25, 29 }
};

int offsetX;
int offsetY;
  
const uint16_t sample_tilesData[] = { 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0xE007, 0x87C2, 0x48EC, 0x48EC, 0x87C2, 0x87C2, 0x87C2, 0xE007, 0x87C2, 0x6781, 0x48EC, 0x48EC, 0x6781, 0x6781, 0x48EC, 0xE007, 0x6781, 0x6781, 0x87C2, 0x87C2, 0x6781, 0x87C2, 0x48EC, 0x87C2, 0x6781, 0x6A31, 0x6781, 0x6781, 0x6A31, 0x87C2, 0x87C2, 0x6781, 0x6781, 0x48EC, 0x87C2, 0x6A31, 0x6781, 0x6781, 0x87C2, 0xE007, 0x6781, 0x87C2, 0x87C2, 0x6781, 0x6781, 0x6781, 0x6A31, 0x87C2, 0x48EC, 0x6781, 0x0621, 0x6781, 0x6781, 0x6781, 0x6A31, 0x6781, 0x87C2, 0x6781, 0x0621, 0x0621, 0x6A31, 0x6A31, 0x6A31, 0xE007, 0x6A31, 0x0621, 0x6781, 0x6A31, 0x0621, 0x0621, 0x0621, 0xE007, 0x6A31, 0x0621, 0x6A31, 0x6A31, 0x0621, 0x0621, 0x0621, 0xE007, 0x87C2, 0x87C2, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0xE007, 0x87C2, 0x87C2, 0x6A31, 0x0621, 0x0621, 0x0621, 0x0621, 0xE007, 0x6781, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0xE007, 0xE007, 0x6A31, 0x0621, 0x6A31, 0x0621, 0x0621, 0x0621, 0xE007, 0xE007, 0x87C2, 0x6781, 0x0621, 0x6A31, 0x0621, 0x0621, 0xE007, 0x6A31, 0x6781, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0x87C2, 0x6781, 0x6A31, 0x0621, 0x6A31, 0x0621, 0x0621, 0x0621, 0x6781, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0xE007, 0x6A31, 0x6A31, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0xE007, 0x87C2, 0x6781, 0x6A31, 0x0621, 0x0621, 0x0621, 0x0621, 0xE007, 0x6781, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0xE007, 0xE007, 0x6A31, 0x0621, 0x6A31, 0x0621, 0x0621, 0x0621, 0x87C2, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0xE007, 0x6A31, 0x0621, 0x6781, 0x6A31, 0x0621, 0x0621, 0x0621, 0xE007, 0x0621, 0x0621, 0x6A31, 0x6A31, 0x0621, 0x0621, 0x0621, 0xE007, 0x6A31, 0x6A31, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0xE007, 0x87C2, 0x6781, 0x6A31, 0x0621, 0x0621, 0x0621, 0x0621, 0xE007, 0x6781, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0xE007, 0xE007, 0x6A31, 0x0621, 0x6A31, 0x0621, 0x0621, 0x0621, 0xE007, 0x6A31, 0x87C2, 0x6781, 0x0621, 0x6A31, 0x0621, 0x0621, 0xE007, 0x6A31, 0x6781, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0x87C2, 0x87C2, 0x48EC, 0x48EC, 0x87C2, 0x87C2, 0x87C2, 0x87C2, 0x48EC, 0x6781, 0x87C2, 0x87C2, 0x6781, 0x48EC, 0x48EC, 0x6781, 0x48EC, 0x87C2, 0x6781, 0x6781, 0x87C2, 0x48EC, 0x48EC, 0x87C2, 0x87C2, 0x87C2, 0x6A31, 0x6781, 0x87C2, 0x87C2, 0x87C2, 0x87C2, 0x87C2, 0x6781, 0x6A31, 0x6A31, 0x6781, 0x87C2, 0x87C2, 0x6781, 0x6781, 0x6A31, 0x6781, 0x6781, 0x6A31, 0x6781, 0x6781, 0x0621, 0x6A31, 0x0621, 0x6781, 0x6781, 0x0621, 0x6A31, 0x6A31, 0x0621, 0x0621, 0x0621, 0x6A31, 0x6A31, 0x0621, 0x6A31, 0x0621, 0x6A31, 0x87C2, 0x87C2, 0x48EC, 0x48EC, 0x87C2, 0x87C2, 0x87C2, 0x87C2, 0x48EC, 0x6781, 0x87C2, 0x87C2, 0x6781, 0x48EC, 0x48EC, 0x6781, 0x48EC, 0x87C2, 0x6781, 0x6781, 0x87C2, 0x48EC, 0x48EC, 0x87C2, 0x87C2, 0x87C2, 0x6A31, 0x6781, 0x87C2, 0x87C2, 0x87C2, 0x87C2, 0x87C2, 0x6781, 0x6A31, 0x6A31, 0x6781, 0x87C2, 0x87C2, 0x6781, 0x6781, 0x6A31, 0x6781, 0x6781, 0x6A31, 0x6781, 0x6781, 0x0621, 0x6A31, 0x0621, 0x6781, 0x6781, 0x0621, 0x6A31, 0x6A31, 0x0621, 0x0621, 0x0621, 0x6A31, 0x6A31, 0x0621, 0x6A31, 0x0621, 0x6A31, 0x48EC, 0x87C2, 0x87C2, 0x48EC, 0x48EC, 0x87C2, 0x87C2, 0x87C2, 0x87C2, 0x87C2, 0x6781, 0x48EC, 0x48EC, 0x6781, 0x6781, 0x48EC, 0x6781, 0x6781, 0x6781, 0x87C2, 0x87C2, 0x6781, 0x87C2, 0x48EC, 0x6781, 0x48EC, 0x48EC, 0x6781, 0x6781, 0x6A31, 0x87C2, 0x87C2, 0x6781, 0x87C2, 0x87C2, 0x6781, 0x6A31, 0x6781, 0x6781, 0x87C2, 0x0621, 0x6781, 0x6781, 0x6A31, 0x0621, 0x6781, 0x6781, 0x6A31, 0x0621, 0x6A31, 0x6A31, 0x6A31, 0x0621, 0x6A31, 0x6A31, 0x0621, 0x6A31, 0x0621, 0x6A31, 0x6A31, 0x0621, 0x0621, 0x0621, 0x0621, 0x87C2, 0x87C2, 0x48EC, 0x48EC, 0x87C2, 0x87C2, 0xE007, 0xE007, 0x48EC, 0x6781, 0x87C2, 0x87C2, 0x6781, 0x48EC, 0x48EC, 0xE007, 0x48EC, 0x87C2, 0x6781, 0x6781, 0x87C2, 0x48EC, 0x48EC, 0x87C2, 0x87C2, 0x87C2, 0x6A31, 0x6781, 0x87C2, 0x87C2, 0x87C2, 0x87C2, 0x87C2, 0x6781, 0x6A31, 0x6A31, 0x6781, 0x87C2, 0x87C2, 0x6781, 0x6781, 0x6A31, 0x6781, 0x6781, 0x6A31, 0x6781, 0x6781, 0xE007, 0x6A31, 0x0621, 0x6781, 0x6781, 0x0621, 0x6A31, 0x87C2, 0x48EC, 0x0621, 0x0621, 0x6A31, 0x6A31, 0x0621, 0x6A31, 0x6781, 0x87C2, 0x0621, 0x0621, 0x0621, 0x6A31, 0x6781, 0x0621, 0x6A31, 0xE007, 0x0621, 0x0621, 0x0621, 0x6A31, 0x6A31, 0x6A31, 0xE007, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x87C2, 0x48EC, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x6A31, 0x87C2, 0x87C2, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x6781, 0xE007, 0x0621, 0x0621, 0x0621, 0x6A31, 0x0621, 0x6A31, 0xE007, 0xE007, 0x0621, 0x0621, 0x6A31, 0x0621, 0x6781, 0x87C2, 0xE007, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x6781, 0xE007, 0xE007, 0x0621, 0x0621, 0x0621, 0x6A31, 0x0621, 0x6781, 0x87C2, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x6781, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x6A31, 0xE007, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x6A31, 0x6781, 0x87C2, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x6781, 0xE007, 0x0621, 0x0621, 0x0621, 0x6A31, 0x0621, 0x6A31, 0xE007, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x87C2, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x6781, 0x0621, 0x0621, 0x0621, 0x6A31, 0x6781, 0x6781, 0x87C2, 0xE007, 0x0621, 0x0621, 0x0621, 0x6A31, 0x6A31, 0x6781, 0x6781, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x6A31, 0xE007, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x6A31, 0x6781, 0x87C2, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x6781, 0xE007, 0x0621, 0x0621, 0x0621, 0x6A31, 0x0621, 0xE007, 0xE007, 0xE007, 0x0621, 0x0621, 0x6A31, 0x0621, 0x6781, 0x87C2, 0xE007, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x6781, 0x6A31, 0xE007, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x6781, 0x0621, 0x0621, 0x0621, 0x0621, 0x6781, 0x0621, 0x6A31, 0x6A31, 0x0621, 0x0621, 0x0621, 0x0621, 0x6A31, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x0621, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x062C, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x062C, 0x062C, 0x6A31, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x8722, 0x062C, 0x6A31, 0x6E32, 0x6E32, 0x6E32, 0x062C, 0x6A31, 0x6A31, 0x8722, 0x8722, 0x6E32, 0x6E32, 0x6E32, 0x8722, 0x062C, 0x6A31, 0x6A31, 0x8722, 0x6E32, 0x6E32, 0x6E32, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x6E32, 0x062C, 0x062C, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6E32, 0x062C, 0x8722, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x6E32, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x062C, 0x8722, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x6A31, 0x062C, 0x062C, 0x8722, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6A31, 0x062C, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x062C, 0x062C, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x062C, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x6A31, 0x6E32, 0x6A31, 0x062C, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6E32, 0x062C, 0x062C, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x062C, 0x062C, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x062C, 0x8722, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x6A31, 0x6E32, 0x6E32, 0x6A31, 0x062C, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x062C, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6A31, 0x062C, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6E32, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x062C, 0x8722, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x6A31, 0x062C, 0x062C, 0x8722, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6A31, 0x062C, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x062C, 0x6E32, 0x6E32, 0x062C, 0x6E32, 0x6E32, 0x6E32, 0x062C, 0x062C, 0x6E32, 0x062C, 0x062C, 0x062C, 0x6E32, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x062C, 0x8722, 0x8722, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x062C, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6A31, 0x062C, 0x062C, 0x6E32, 0x062C, 0x6E32, 0x6E32, 0x062C, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x8722, 0x062C, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x062C, 0x6E32, 0x062C, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x062C, 0x062C, 0x6A31, 0x062C, 0x062C, 0x6E32, 0x8722, 0x062C, 0x062C, 0x8722, 0x6A31, 0x8722, 0x8722, 0x6E32, 0x8722, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x062C, 0x6E32, 0x6E32, 0x062C, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x062C, 0x062C, 0x6E32, 0x062C, 0x062C, 0x6E32, 0x6E32, 0x6E32, 0x8722, 0x062C, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x6E32, 0x062C, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x062C, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x8722, 0x8722, 0x8722, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x062C, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6A31, 0x062C, 0x062C, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6A31, 0x062C, 0x8722, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x8722, 0x8722, 0x6A31, 0x6A31, 0x062C, 0x6E32, 0x6E32, 0x6E32, 0x8722, 0x6A31, 0x6A31, 0x062C, 0x8722, 0x6E32, 0x6E32, 0x6E32, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x6A31, 0x6E32, 0x6E32, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x062C, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x6E32, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x062C, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x6A31, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x062C, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x6A31, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x062C, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x062C, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x6A31, 0x6E32, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x062C, 0x062C, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x6A31, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6E32, 0x6E32, 0x6A31, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x8722, 0x062C, 0x6E32, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x6A31, 0x6E32, 0x6A31, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x062C, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x8722, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x062C, 0x062C, 0x6A31, 0x6A31, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x8722, 0x062C, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x8722, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6A31, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32, 0x6E32 };
uint16_t buffer1[W * 8];
uint16_t buffer2[W * 8];

inline void drawTileRow(uint16_t *buffer, const int bufferOffset, const int tileOffset, const int yOffsetRemainder, const int xOffsetRemainder, const int y, const int x) __attribute__((always_inline));

void setup() {
  gb.begin();
  gb.display.init(0, 0, ColorMode::rgb565);
  gb.setFrameRate(40);
  
  SerialUSB.begin(9600);
}

void loop() {
  while (!gb.update());

  if (gb.buttons.repeat(Button::right, 0)) {
    //if (LAYER_WIDTH * 8 - offsetX > W) {
      offsetX += 2;
    //}
  }
  if (gb.buttons.repeat(Button::left, 0)) {
    //if (offsetX > 0) {
      offsetX -= 2;
    //}

    if (offsetX < 0) offsetX += LAYER_WIDTH * 8 * 2;
  }
  if (gb.buttons.repeat(Button::down, 0)) {
    if (LAYER_HEIGHT * 8 - offsetY > H) {
      offsetY += 2;
    }
  }
  if (gb.buttons.repeat(Button::up, 0)) {
    if (offsetY > 0) {
      offsetY -= 2;
    }
  }
  
  draw();

  if (gb.frameCount % 25 == 0) SerialUSB.printf("CPU: %i\n", gb.getCpuLoad());
}

void draw() {
  int tileOffset, bufferOffset;
  
  // Draw slices of the screen, each 8 pixels tall
  for (int sliceIndex = 0; sliceIndex < H / SLICE_HEIGHT; sliceIndex++) {
    // 2 buffers so we can be filling the next one while the current one is being sent to the screen
    uint16_t *buffer = sliceIndex % 2 == 0 ? (uint16_t *)&buffer1 : (uint16_t *)&buffer2;

    // Draw the background layer, no transparency
    int yIndex = (offsetY / 2) / TILE_SIZE + sliceIndex;
    int yOffsetRemainder = (offsetY / 2) % TILE_SIZE;

    int xIndexStart = (offsetX / 2) / TILE_SIZE;
    int xOffsetRemainder = (offsetX / 2) % TILE_SIZE;

    // Partial right block
    
    tileOffset = layer2[yIndex][xIndexStart % LAYER_WIDTH] * TILE_SIZE * TILE_SIZE;

    for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
      for (int x = xOffsetRemainder; x < TILE_SIZE; x++) {
        buffer[x - xOffsetRemainder + (y - yOffsetRemainder) * W] = sample_tilesData[tileOffset + x + y * TILE_SIZE];
      }
    }
    
    // Handle bottom half of tiles in this slice
    tileOffset = layer2[yIndex+1][xIndexStart % LAYER_WIDTH] * TILE_SIZE * TILE_SIZE;
    
    for (int y = 0; y < yOffsetRemainder; y++) {
      for (int x = xOffsetRemainder; x < TILE_SIZE; x++) {
        buffer[x - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * W] = sample_tilesData[tileOffset + x + y * TILE_SIZE];
      }
    }

    for (int xIndexOffset = 1; xIndexOffset < W / TILE_SIZE; xIndexOffset++) {
      tileOffset = layer2[yIndex][(xIndexStart + xIndexOffset) % LAYER_WIDTH] * TILE_SIZE * TILE_SIZE;
      bufferOffset = xIndexOffset * TILE_SIZE;
      
      for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
        buffer[bufferOffset + 0 - xOffsetRemainder + (y - yOffsetRemainder) * W] = sample_tilesData[tileOffset + 0 + y * TILE_SIZE];
        buffer[bufferOffset + 1 - xOffsetRemainder + (y - yOffsetRemainder) * W] = sample_tilesData[tileOffset + 1 + y * TILE_SIZE];
        buffer[bufferOffset + 2 - xOffsetRemainder + (y - yOffsetRemainder) * W] = sample_tilesData[tileOffset + 2 + y * TILE_SIZE];
        buffer[bufferOffset + 3 - xOffsetRemainder + (y - yOffsetRemainder) * W] = sample_tilesData[tileOffset + 3 + y * TILE_SIZE];
        buffer[bufferOffset + 4 - xOffsetRemainder + (y - yOffsetRemainder) * W] = sample_tilesData[tileOffset + 4 + y * TILE_SIZE];
        buffer[bufferOffset + 5 - xOffsetRemainder + (y - yOffsetRemainder) * W] = sample_tilesData[tileOffset + 5 + y * TILE_SIZE];
        buffer[bufferOffset + 6 - xOffsetRemainder + (y - yOffsetRemainder) * W] = sample_tilesData[tileOffset + 6 + y * TILE_SIZE];
        buffer[bufferOffset + 7 - xOffsetRemainder + (y - yOffsetRemainder) * W] = sample_tilesData[tileOffset + 7 + y * TILE_SIZE];
      }

      tileOffset = layer2[yIndex + 1][(xIndexStart + xIndexOffset) % LAYER_WIDTH] * TILE_SIZE * TILE_SIZE;
      
      for (int y = 0; y < yOffsetRemainder; y++) {
        buffer[bufferOffset + 0 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * W] = sample_tilesData[tileOffset + 0 + y * TILE_SIZE];
        buffer[bufferOffset + 1 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * W] = sample_tilesData[tileOffset + 1 + y * TILE_SIZE];
        buffer[bufferOffset + 2 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * W] = sample_tilesData[tileOffset + 2 + y * TILE_SIZE];
        buffer[bufferOffset + 3 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * W] = sample_tilesData[tileOffset + 3 + y * TILE_SIZE];
        buffer[bufferOffset + 4 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * W] = sample_tilesData[tileOffset + 4 + y * TILE_SIZE];
        buffer[bufferOffset + 5 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * W] = sample_tilesData[tileOffset + 5 + y * TILE_SIZE];
        buffer[bufferOffset + 6 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * W] = sample_tilesData[tileOffset + 6 + y * TILE_SIZE];
        buffer[bufferOffset + 7 - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * W] = sample_tilesData[tileOffset + 7 + y * TILE_SIZE];
      }
    }

    // Paritial left block

    tileOffset = layer2[yIndex][(xIndexStart + W / TILE_SIZE) % LAYER_WIDTH] * TILE_SIZE * TILE_SIZE;

    for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
      for (int x = 0; x < xOffsetRemainder; x++) {
        buffer[W + x - xOffsetRemainder + (y - yOffsetRemainder) * W] = sample_tilesData[tileOffset + x + y * TILE_SIZE];
      }
    }
    
    // Handle bottom half of tiles in this slice
    tileOffset = layer2[yIndex+1][(xIndexStart + W / TILE_SIZE) % 30] * TILE_SIZE * TILE_SIZE;
    
    for (int y = 0; y < yOffsetRemainder; y++) {
      for (int x = 0; x < xOffsetRemainder; x++) {
        buffer[W + x - xOffsetRemainder + (y - yOffsetRemainder + TILE_SIZE) * W] = sample_tilesData[tileOffset + x + y * TILE_SIZE];
      }
    }    

    // Draw the foreground layer, with transparency
    yIndex = offsetY / TILE_SIZE + sliceIndex;
    yOffsetRemainder = offsetY % TILE_SIZE;

    xIndexStart = offsetX / TILE_SIZE;
    xOffsetRemainder = offsetX % TILE_SIZE;

    // Partial right block

    tileOffset = layer1[yIndex][xIndexStart % LAYER_WIDTH] * TILE_SIZE * TILE_SIZE;

    for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
      for (int x = xOffsetRemainder; x < TILE_SIZE; x++) {
        drawTileRow(buffer, 0, tileOffset, yOffsetRemainder, xOffsetRemainder, y, x);
      }
    }
    
    // Handle bottom half of tiles in this slice
    tileOffset = layer1[yIndex+1][xIndexStart % LAYER_WIDTH] * TILE_SIZE * TILE_SIZE;
    
    for (int y = 0; y < yOffsetRemainder; y++) {
      for (int x = xOffsetRemainder; x < TILE_SIZE; x++) {
        drawTileRow(buffer, 0, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, x);
      }
    }      
    
    for (int xIndexOffset = 1; xIndexOffset < W / TILE_SIZE; xIndexOffset++) {
      // Handle top half of tiles in this slice
      tileOffset = layer1[yIndex][(xIndexStart + xIndexOffset) % LAYER_WIDTH] * TILE_SIZE * TILE_SIZE;
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
      tileOffset = layer1[yIndex+1][(xIndexStart + xIndexOffset) % 30] * TILE_SIZE * TILE_SIZE;
      
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

    tileOffset = layer1[yIndex][(xIndexStart + W / TILE_SIZE) % LAYER_WIDTH] * TILE_SIZE * TILE_SIZE;

    for (int y = yOffsetRemainder; y < TILE_SIZE; y++) {
      for (int x = 0; x < xOffsetRemainder; x++) {
        drawTileRow(buffer, W, tileOffset, yOffsetRemainder, xOffsetRemainder, y, x);
      }
    }
    
    // Handle bottom half of tiles in this slice
    tileOffset = layer1[yIndex+1][(xIndexStart + W / TILE_SIZE) % LAYER_WIDTH] * TILE_SIZE * TILE_SIZE;
    
    for (int y = 0; y < yOffsetRemainder; y++) {
      for (int x = 0; x < xOffsetRemainder; x++) {
        drawTileRow(buffer, W, tileOffset, yOffsetRemainder - TILE_SIZE, xOffsetRemainder, y, x);
      }
    }    

    gb.tft.andy();
    gb.tft.drawBuffer(0, sliceIndex * SLICE_HEIGHT, buffer, W, SLICE_HEIGHT);
  }
}

inline void drawTileRow(uint16_t *buffer, const int bufferOffset, const int tileOffset, const int yOffsetRemainder, const int xOffsetRemainder, const int y, const int x) {
  if ((sample_tilesData[tileOffset + x + y * TILE_SIZE]) != 0xE007) {
    buffer[bufferOffset + x - xOffsetRemainder + (y - yOffsetRemainder) * W] = sample_tilesData[tileOffset + x + y * TILE_SIZE];
  }
}

