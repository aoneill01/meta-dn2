#include "DisappearingTiles.h"
#include "TiledDisplay.h"
#include "Level.h"

void DisappearingTiles::loadLevel() {
    count = 0;
    tickCount = 0;

    // TODO Remove magic numbers
    for (int x = 0; x < 64; x++) {
        for (int y = 0; y < 80; y++) {
            // TODO Refactor
            uint8_t originalTile = TiledDisplay::layer1[y][x];
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
                TiledDisplay::layer1[tiles[i].y][tiles[i].x] = 21;
            }
            // Must be 5
            else {
                TiledDisplay::layer1[tiles[i].y][tiles[i].x] = tiles[i].originalTile;
            }
        }
    }
    else if (tickCount % 64 == 32) {
        for (int i = 0; i < count; i++) {
            if (Level::typeMap[tiles[i].originalTile] == 4) {
                TiledDisplay::layer1[tiles[i].y][tiles[i].x] = tiles[i].originalTile;
            }
            // Must be 5
            else {
                TiledDisplay::layer1[tiles[i].y][tiles[i].x] = 21;
            }
        }
    }

    tickCount++;
}