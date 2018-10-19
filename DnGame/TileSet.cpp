#include <Gamebuino-Meta.h>
#include "TileSet.h"

bool TileSet::add(int x, int y, byte propety) {
    if (count >= TILE_SET_MAX_COUNT) {
        return false;
    }

    for (int i = 0; i < count; i++) {
        if (tiles[i].x == x && tiles[i].y == y) return false;
    }

    tiles[count].x = x;
    tiles[count].y = y;
    tiles[count].propety = propety;

    count++;

    return true;
}

void TileSet::clear() {
    count = 0;
}

bool TileSet::isEmpty() {
    return count == 0;
}

bool TileSet::containsTile(byte propety) {
    for (int i = 0; i < count; i++) {
        if (tiles[i].propety == propety) return true;
    }

    return false;
}

int TileSet::getCount() {
    return count;
}

TileInfo TileSet::getTileInfo(int index) {
    if (index < count) {
        return tiles[index];
    }

    TileInfo bad;
    return bad;
}