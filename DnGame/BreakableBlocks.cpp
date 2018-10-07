#include <Gamebuino-Meta.h>
#include "BreakableBlocks.h"
#include "TiledDisplay.h"

bool BreakableBlocks::triggerBlockAt(int x, int y) {
    if (count >= BREAKABLE_BLOCKS_MAX_COUNT) {
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

void BreakableBlocks::clear() {
    count = 0;
}

void BreakableBlocks::handleTick(Level& level) {
    for (int i = 0; i < count; i++) {
        tiles[i].countdown--;
        if (tiles[i].countdown == 0) {
            level.clearTile(tiles[i].x, tiles[i].y);

            for (int j = i; j < count - 1; j++) {
                tiles[j] = tiles[j + 1];
            }
            i--;
            count--;
            continue;
        }
        else if (tiles[i].countdown < 10) {
            // TODO Find a better way to do this:
            TiledDisplay::layer1[tiles[i].y][tiles[i].x] = 114;
        }
        else if (tiles[i].countdown < 20) {
            // TODO Find a better way to do this:
            TiledDisplay::layer1[tiles[i].y][tiles[i].x] = 113;
        }
        else {
            // TODO Find a better way to do this:
            TiledDisplay::layer1[tiles[i].y][tiles[i].x] = 98;
        }
    }
}
