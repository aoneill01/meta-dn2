#include "DisappearingTiles.h"

DisappearingTiles::DisappearingTiles(Level *level) {
    this->level = level;
}

void DisappearingTiles::loadLevel() {
    count = 0;
    tickCount = 0;

    for (int x = 0; x < LEVEL_COLS; x++) {
        for (int y = 0; y < LEVEL_ROWS; y++) {
            // TODO Refactor
            uint8_t originalTile = level->getTile(x, y);
            if (Level::typeMap[originalTile] == 4 || Level::typeMap[originalTile] == 5) {
                tiles[count].x = x;
                tiles[count].y = y;
                tiles[count].originalTile = originalTile;
                count++;
            }

            if (count == DISAPPEARING_TILES_MAX_COUNT) return;
        }
    }
}

void DisappearingTiles::handleTick() {
    if (tickCount % 64 == 0) {
        for (int i = 0; i < count; i++) {
            if (Level::typeMap[tiles[i].originalTile] == 4) {
                level->setTile(tiles[i].x, tiles[i].y, 21);
            }
            // Must be 5
            else {
                level->setTile(tiles[i].x, tiles[i].y, tiles[i].originalTile);
            }
        }
    }
    else if (tickCount % 64 == 32) {
        for (int i = 0; i < count; i++) {
            if (Level::typeMap[tiles[i].originalTile] == 4) {
                level->setTile(tiles[i].x, tiles[i].y, tiles[i].originalTile);
            }
            // Must be 5
            else {
                level->setTile(tiles[i].x, tiles[i].y, 21);
            }
        }
    }

    tickCount++;
}