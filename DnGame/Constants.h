#pragma once

// Screen width and height in pixels
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128

#define TILE_SIZE 8
#define SLICE_HEIGHT 8

// Number of tiles in x and y directions per level
#define FOREGROUND_WIDTH 64
#define FOREGROUND_HEIGHT 80

// Number of tiles in x and y directions for paralax background
#define BACKGROUND_WIDTH 37
#define BACKGROUND_HEIGHT 44

// ID of empty space tile
#define EMPTY_TILE 21
// ID of first breaking tile
#define BREAK1_TILE 98
// ID of second breaking tile
#define BREAK2_TILE 113
// ID of third breaking tile
#define BREAK3_TILE 114

#define LEVEL_TILE_SIZE 16

// Tile properties
#define PROP_EMPTY 0
#define PROP_SOLID 1
#define PROP_DEATH 2
#define PROP_BREAK 3
#define PROP_DISA1 4
#define PROP_DISA2 5
#define PROP_UP 6
#define PROP_DOWN 7