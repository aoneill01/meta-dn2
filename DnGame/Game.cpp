#include <Gamebuino-Meta.h>
#include "Game.h"

// TODO Fix magic numbers
const int goalCharacterX = (160 - 32) / 2 + 8;
const int goalCharacterY = (128 - 32) / 2 + 8;

void Game::reset() {
  this->player.resetPosition(this->level);
}
void Game::handleTick() {
  this->player.update(this->level);

  int offsetX = player.getX() - goalCharacterX;
  int offsetY = player.getY() - goalCharacterY;

  this->tiledDisplay.setOffset(offsetX, offsetY);
  
  int characterX = player.getX() - this->tiledDisplay.offsetX - 8;
  int characterY = player.getY() - this->tiledDisplay.offsetY - 8;

  this->tiledDisplay.setCharacterPosition(characterX, characterY);

  this->tiledDisplay.draw();
}

