#pragma once

#define TILE_SET_MAX_COUNT 6

struct TileInfo {
    int x, y;
    byte tile;
};

class TileSet {
    TileInfo tiles[TILE_SET_MAX_COUNT];
    int count = 0;
public:
    bool add(int x, int y, byte tile);
    void clear();
    bool isEmpty();
    bool containsTile(byte tile);
    int getCount();
    TileInfo getTileInfo(int index);
};
