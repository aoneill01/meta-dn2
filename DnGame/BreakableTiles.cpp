#include <Gamebuino-Meta.h>
#include "BreakableTiles.h"

bool BreakableTiles::triggerBlockAt(int x, int y) {
    if (count >= BREAKABLE_TILES_MAX_COUNT) {
        return false;
    }

    for (int i = 0; i < count; i++) {
        if (tiles[i].x == x && tiles[i].y == y) return false;
    }

    tiles[count].x = x;
    tiles[count].y = y;
    tiles[count].countdown = BREAKABLE_TILES_COUNTDOWN;

    count++;

    return true;
}

void BreakableTiles::clear() {
    count = 0;
}

void BreakableTiles::handleTick(Level& level) {
    for (int i = 0; i < count; i++) {
        tiles[i].countdown--;
        if (tiles[i].countdown == 0) {
            level.setTile(tiles[i].x, tiles[i].y, EMPTY_TILE);

            for (int j = i; j < count - 1; j++) {
                tiles[j] = tiles[j + 1];
            }
            i--;
            count--;
            continue;
        }
        else if (tiles[i].countdown < 10) {
            level.setTile(tiles[i].x, tiles[i].y, BREAK3_TILE);
        }
        else if (tiles[i].countdown < 20) {
            level.setTile(tiles[i].x, tiles[i].y, BREAK2_TILE);
        }
        else {
            level.setTile(tiles[i].x, tiles[i].y, BREAK1_TILE);
        }
    }
}
