#pragma once

#define TILE_SET_MAX_COUNT 6

struct TileInfo {
    int x, y;
    byte propety;
};

class TileSet {
    TileInfo tiles[TILE_SET_MAX_COUNT];
    int count = 0;
public:
    bool add(int x, int y, byte propety);
    void clear();
    bool isEmpty();
    bool containsTile(byte propety);
    int getCount();
    TileInfo getTileInfo(int index);
};
