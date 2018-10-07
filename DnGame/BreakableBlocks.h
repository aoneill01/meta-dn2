#pragma once
#include "TiledDisplay.h"
#include "Level.h"

#define BREAKABLE_BLOCKS_MAX_COUNT 16

struct BreakableBlockInfo {
    int x, y;
    byte countdown;
};

class BreakableBlocks {
    BreakableBlockInfo tiles[BREAKABLE_BLOCKS_MAX_COUNT];
    int count = 0;
public:
    bool triggerBlockAt(int x, int y);
    void clear();
    void handleTick(Level& level);
};
