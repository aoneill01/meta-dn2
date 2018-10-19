#include <Gamebuino-Meta.h>
#include "Game.h"

const int goalCharacterX = (SCREEN_WIDTH - 20) / 2 + 3;
const int goalCharacterY = (SCREEN_HEIGHT - 28) / 2 + 2;

void Game::loadLevel() {
  disappearingTiles.loadLevel(level);
  reset();
}

void Game::reset() {
  player.resetPosition(level);
}

void Game::handleTick() {
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
    reset();
    return;
  }

  int offsetX = player.getX() - goalCharacterX;
  int offsetY = player.getY() - goalCharacterY;

  tiledDisplay.setOffset(offsetX, offsetY);
  
  int characterX = player.getX() - tiledDisplay.offsetX - 3;
  int characterY = player.getY() - tiledDisplay.offsetY - 2;

  tiledDisplay.setCharacterPosition(characterX, characterY);
  tiledDisplay.setCharacterFrame(player.animationFrame);
  tiledDisplay.characterFlipped = player.facingLeft;

  tiledDisplay.draw();
}
