#include <Gamebuino-Meta.h>
#include "Game.h"

// TODO Fix magic numbers
const int goalCharacterX = (160 - 20) / 2 + 3;
const int goalCharacterY = (128 - 28) / 2 + 2;

void Game::reset() {
  player.resetPosition(level);
}
void Game::handleTick() {
  player.update(level);

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
