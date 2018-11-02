#pragma once

#include <Gamebuino-Meta.h>

// Tile ids for the paralax background
extern const uint8_t backgroundLayer[];

// Pixel data for the 16x16 pixel tiles, split into 8x8 regions for rendering
extern const uint16_t tilesData[];

// Pixel data for the different frames of the main character
extern const uint16_t characterData[];

// Pixel data for 5x8 pixel sprites, mainly digits
extern const uint16_t charsData[];