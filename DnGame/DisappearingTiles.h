#pragma once
#include <Gamebuino-Meta.h>

#define DISAPPEARING_TILES_MAX_COUNT 50

struct DisappearingTileInfo {
    uint8_t x, y, originalTile;
};

class DisappearingTiles {
    DisappearingTileInfo tiles[DISAPPEARING_TILES_MAX_COUNT];
    int count = 0;
    int tickCount = 0;
public:
    void loadLevel();
    void handleTick();
};
