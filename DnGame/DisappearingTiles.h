#pragma once
#include <Gamebuino-Meta.h>
#include "Level.h"
#include "TiledDisplay.h"

#define DISAPPEARING_TILES_MAX_COUNT 50
#define TICK_COUNT_CYCLE 64

struct DisappearingTileInfo {
    uint8_t x, y, originalTile;
};

class DisappearingTiles {
    DisappearingTileInfo tiles[DISAPPEARING_TILES_MAX_COUNT];
    int count = 0;
    int tickCount = 0;
public:
    void loadLevel(Level &level);
    void handleTick(Level &level);
};
