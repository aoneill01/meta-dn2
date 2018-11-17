#pragma once

#define TILE_SET_MAX_COUNT 6

struct TileInfo {
    int x, y;
    byte property;
};

class TileSet {
    TileInfo tiles[TILE_SET_MAX_COUNT];
    int count = 0;
public:
    bool ignoreDisappearing = false;

    bool add(int x, int y, byte property);
    void clear();
    bool isEmpty();
    bool containsTile(byte property);
    int getCount();
    TileInfo getTileInfo(int index);
};
