#include <Gamebuino-Meta.h>
#include "Game.h"
#include "GraphicsData.h"

const int goalCharacterX = (SCREEN_WIDTH - 20) / 2 + 3;
const int goalCharacterY = (SCREEN_HEIGHT - 28) / 2 + 2;

void Game::loadLevel() {
  level.loadLevel(levelNumber);
  disappearingTiles.loadLevel(level);
  player.resetPosition(level);

  tiledDisplay.sprites[4].data = (uint16_t*)&charsData + (deaths % 10) * 40;
  tiledDisplay.sprites[3].data = (uint16_t*)&charsData + ((deaths / 10) % 10) * 40;
  tiledDisplay.sprites[2].data = (uint16_t*)&charsData + ((deaths / 100) % 10) * 40;

  tiledDisplay.sprites[7].data = (uint16_t*)&charsData + ((50 - levelNumber) % 10) * 40;
  tiledDisplay.sprites[6].data = (uint16_t*)&charsData + (((50 - levelNumber) / 10) % 10) * 40;
}

void Game::handleTick() {
  if (player.nextLevel) {
    levelNumber++;
    if (levelNumber == 4) levelNumber = 1;
    loadLevel();
  }

  player.handleTick(level, breakableTiles);
  breakableTiles.handleTick(level);
  disappearingTiles.handleTick(level);

  if (player.isDead()) {
    for (int j = 0; j < 4; j++) {
      tiledDisplay.pixelMask = 0b0000000011111000;
      for (int i = 0; i < 6; i++) {
        tiledDisplay.draw();
        while (!gb.update());
      }

      tiledDisplay.pixelMask = 0b0000000001111000;
      for (int i = 0; i < 6; i++) {
        tiledDisplay.draw();
        while (!gb.update());
      }
    }

    tiledDisplay.pixelMask = 0xffff;
    
    deaths++;
    loadLevel();

    return;
  }

  int offsetX = player.getX() - goalCharacterX;
  int offsetY = player.getY() - goalCharacterY;

  tiledDisplay.setOffset(offsetX, offsetY);
  
  int characterX = player.getX() - tiledDisplay.offsetX - 3;
  int characterY = player.getY() - tiledDisplay.offsetY - 2;

  tiledDisplay.setCharacterPosition(characterX, characterY);
  tiledDisplay.setCharacterFrame(player.animationFrame);
  tiledDisplay.setCharacterFlipped(player.facingLeft);

  int i = 0;
  for (; i < breakableTiles.fragments.getCount(); i++) {
    FragmentSprite sprite = breakableTiles.fragments.getSprite(i);
    tiledDisplay.sprites[8 + i].x = sprite.getX() - tiledDisplay.offsetX;
    tiledDisplay.sprites[8 + i].y = sprite.getY() - tiledDisplay.offsetY;
  }
  for (; i < 12; i++) {
    tiledDisplay.sprites[8 + i].x = -5;
    tiledDisplay.sprites[8 + i].x = -8;
  }

  tiledDisplay.draw();
}
