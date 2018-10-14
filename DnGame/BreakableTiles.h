#pragma once
#include "TiledDisplay.h"
#include "Level.h"

#define BREAKABLE_TILES_MAX_COUNT 16

struct BreakableTileInfo {
    int x, y;
    byte countdown;
};

class BreakableTiles {
    BreakableTileInfo tiles[BREAKABLE_TILES_MAX_COUNT];
    int count = 0;
public:
    bool triggerBlockAt(int x, int y);
    void clear();
    void handleTick(Level& level);
};
