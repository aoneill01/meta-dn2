#pragma once
#define FIXED_POINTS_NO_RANDOM
#include <FixedPoints.h>
#include <FixedPointsCommon.h>
#include "TiledDisplay.h"
#include "Level.h"

#define BREAKABLE_TILES_MAX_COUNT 16
#define BREAKABLE_TILES_COUNTDOWN 30
#define FRAGMENT_SPRITES_MAX_COUNT 12
#define FRAGMENT_COUNTDOWN 100

struct BreakableTileInfo {
    int x, y;
    byte countdown;
};

class FragmentSprite {
    SQ15x16 x, y;
    SQ15x16 velX, velY;
    uint8_t tickCountdown = FRAGMENT_COUNTDOWN;
public:
    FragmentSprite() {}
    FragmentSprite(SQ15x16 x, SQ15x16 y);
    bool handleTick(Level &level);
    int getX();
    int getY();
};

class FragmentSprites {
    FragmentSprite sprites[FRAGMENT_SPRITES_MAX_COUNT];
    int count = 0;
public:
    void add(int x, int y);
    void clear();
    int getCount();
    FragmentSprite getSprite(int index);
    void handleTick(Level &level);
};

class BreakableTiles {
    BreakableTileInfo tiles[BREAKABLE_TILES_MAX_COUNT];
    int count = 0;
public:
    FragmentSprites fragments;
    bool triggerBlockAt(int x, int y);
    void clear();
    void handleTick(Level& level);
};
