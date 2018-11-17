#include "DisappearingTiles.h"
#include "Constants.h"

void DisappearingTiles::loadLevel(Level &level) {
    count = 0;
    tickCount = 0;

    for (int x = 0; x < FOREGROUND_WIDTH; x++) {
        for (int y = 0; y < FOREGROUND_HEIGHT; y++) {
            uint8_t originalTile = level.getTile(x, y);
            if (Level::typeMap[originalTile] == PROP_DISA1 || Level::typeMap[originalTile] == PROP_DISA2) {
                tiles[count].x = x;
                tiles[count].y = y;
                tiles[count].originalTile = originalTile;
                count++;
            }

            if (count == DISAPPEARING_TILES_MAX_COUNT) return;
        }
    }
}

void DisappearingTiles::handleTick(Level &level) {
    if (tickCount % TICK_COUNT_CYCLE == 0) {
        for (int i = 0; i < count; i++) {
            if (Level::typeMap[tiles[i].originalTile] == PROP_DISA1) {
                level.setTile(tiles[i].x, tiles[i].y, EMPTY_TILE);
            }
            // Must be PROP_DISA1
            else {
                level.setTile(tiles[i].x, tiles[i].y, tiles[i].originalTile);
            }
        }
    }
    else if (tickCount % TICK_COUNT_CYCLE == TICK_COUNT_CYCLE / 2) {
        for (int i = 0; i < count; i++) {
            if (Level::typeMap[tiles[i].originalTile] == PROP_DISA1) {
                level.setTile(tiles[i].x, tiles[i].y, tiles[i].originalTile);
            }
            // Must be PROP_DISA1
            else {
                level.setTile(tiles[i].x, tiles[i].y, EMPTY_TILE);
            }
        }
    }

    tickCount++;
}
