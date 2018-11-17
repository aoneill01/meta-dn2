#include <Gamebuino-Meta.h>
#include "TileSet.h"
#include "Constants.h"

bool TileSet::add(int x, int y, byte property) {
    if (count >= TILE_SET_MAX_COUNT) {
        return false;
    }

    if (ignoreDisappearing && (property == PROP_DISA1 || property == PROP_DISA2)) {
        return false;
    }

    for (int i = 0; i < count; i++) {
        if (tiles[i].x == x && tiles[i].y == y) return false;
    }

    tiles[count].x = x;
    tiles[count].y = y;
    tiles[count].property = property;

    count++;

    return true;
}

void TileSet::clear() {
    count = 0;
}

bool TileSet::isEmpty() {
    return count == 0;
}

bool TileSet::containsTile(byte property) {
    for (int i = 0; i < count; i++) {
        if (tiles[i].property == property) return true;
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