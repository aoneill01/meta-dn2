#include <Gamebuino-Meta.h>
#include "BreakableTiles.h"
#include "TiledDisplay.h"

bool BreakableTiles::triggerBlockAt(int x, int y) {
    if (count >= BREAKABLE_TILES_MAX_COUNT) {
        return false;
    }

    for (int i = 0; i < count; i++) {
        if (tiles[i].x == x && tiles[i].y == y) return false;
    }

    tiles[count].x = x;
    tiles[count].y = y;
    tiles[count].countdown = 30;

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
            level.setTile(tiles[i].x, tiles[i].y, 21);

            for (int j = i; j < count - 1; j++) {
                tiles[j] = tiles[j + 1];
            }
            i--;
            count--;
            continue;
        }
        else if (tiles[i].countdown < 10) {
            level.setTile(tiles[i].x, tiles[i].y, 114);
        }
        else if (tiles[i].countdown < 20) {
            level.setTile(tiles[i].x, tiles[i].y, 113);
        }
        else {
            level.setTile(tiles[i].x, tiles[i].y, 98);
        }
    }
}
