#include <Gamebuino-Meta.h>
#include "Level.h"
#include "Constants.h"

const uint8_t Level::typeMap[] = {
  PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, 
  PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_EMPTY, PROP_SOLID, PROP_SOLID, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, 
  PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, 
  PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, 
  PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_DEATH, PROP_DEATH, PROP_DEATH, PROP_SOLID, PROP_SOLID, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_DISA1, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_DISA2, 
  PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_DEATH, PROP_SOLID, PROP_SOLID, PROP_SOLID, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_DISA1, PROP_EMPTY, PROP_EMPTY, PROP_EMPTY, PROP_DISA2, 
  PROP_DISA1, PROP_BREAK, PROP_BREAK, PROP_SOLID, PROP_DEATH, PROP_SOLID, PROP_EMPTY, PROP_EMPTY, PROP_DISA2, PROP_DISA2, PROP_DISA1, PROP_DISA1, PROP_DISA2, PROP_DISA2, PROP_DISA2, PROP_DISA2, 
  PROP_DISA2, PROP_BREAK, PROP_BREAK, PROP_DEATH, PROP_DEATH, PROP_DEATH, PROP_EMPTY, PROP_EMPTY, PROP_DISA2, PROP_DISA2, PROP_DISA1, PROP_DISA1, PROP_DISA1, PROP_DISA1, PROP_DISA1, PROP_DISA1
};

Level::Level(TiledDisplay *tiledDisplay) {
  this->tiledDisplay = tiledDisplay;
}

bool Level::collisionsAt(int x, int y, int width, int height, TileSet& result) {
  byte tile;
  result.clear();

  // TODO handle width > 16
  for (int yTest = y; yTest < y + height - 1; yTest += 16) {
    tile = tileAt(x, yTest);
    if (tile) result.add(x / LEVEL_TILE_SIZE, yTest / LEVEL_TILE_SIZE, tile);
    tile = tileAt(x + width - 1, yTest);
    if (tile) result.add((x + width - 1) / LEVEL_TILE_SIZE, yTest / LEVEL_TILE_SIZE, tile);
  }

  tile = tileAt(x, y + height - 1);
  if (tile) result.add(x / LEVEL_TILE_SIZE, (y + height - 1) / LEVEL_TILE_SIZE, tile);
  tile = tileAt(x + width - 1, y + height - 1);
  if (tile) result.add((x + width - 1) / LEVEL_TILE_SIZE, (y + height - 1) / LEVEL_TILE_SIZE, tile);

  return !result.isEmpty();
}

byte Level::tileAt(int x, int y) {
  int gridX = x / LEVEL_TILE_SIZE;
  int gridY = y / LEVEL_TILE_SIZE;

  // Solid outside of map
  if (gridX < 0 || gridX >= FOREGROUND_WIDTH) return PROP_SOLID;
  if (gridY < 0) return PROP_UP;
  if (gridY >= FOREGROUND_HEIGHT) return PROP_DOWN;

  int i = tiledDisplay->foregroundLayer[FOREGROUND_WIDTH * gridY + gridX];
  if (i > 16 * 8) {
    if (gb.buttons.repeat(Button::a, 0)) return PROP_EMPTY;
    i -= 16 * 8;
  } 
  uint8_t value = typeMap[i];
  
  if (value == 2) {
    // Damage tiles have a 1 pixel buffer of empty space
    if ((x % LEVEL_TILE_SIZE) == 0 || (x % LEVEL_TILE_SIZE) == LEVEL_TILE_SIZE - 1 ||
      (y % LEVEL_TILE_SIZE) == 0 || (y % LEVEL_TILE_SIZE) == LEVEL_TILE_SIZE - 1) return 0;
  }
  return value;
}

void Level::setTile(int x, int y, uint8_t tile) {
  tiledDisplay->foregroundLayer[FOREGROUND_WIDTH * y + x] = tile;
}

uint8_t Level::getTile(int x, int y) {
  return tiledDisplay->foregroundLayer[FOREGROUND_WIDTH * y + x];
}

void Level::loadLevel(int levelNumber) {
  char filename[256];
  snprintf(filename, sizeof filename, "levels/%d.dnl", levelNumber);
  File levelFile = SD.open(filename, FILE_READ);

  for (int y = 0; y < FOREGROUND_HEIGHT; y++) {
    for (int x = 0; x < FOREGROUND_WIDTH; x++) {
      // setTile(x, y, levelFile.read());
    }
  }
}
