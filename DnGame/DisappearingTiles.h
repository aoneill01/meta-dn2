#pragma once
#include <Gamebuino-Meta.h>
#include "Level.h"

#define DISAPPEARING_TILES_MAX_COUNT 50

struct DisappearingTileInfo {
    uint8_t x, y, originalTile;
};

class DisappearingTiles {
    Level *level;
    DisappearingTileInfo tiles[DISAPPEARING_TILES_MAX_COUNT];
    int count = 0;
    int tickCount = 0;
public:
    DisappearingTiles(Level *level);
    void loadLevel();
    void handleTick();
};
