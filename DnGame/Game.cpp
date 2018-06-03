#include <Gamebuino-Meta.h>
#include "Game.h"

// TODO Fix magic numbers
const int goalCharacterX = (160 - 20) / 2 + 3;
const int goalCharacterY = (128 - 28) / 2 + 4;

void Game::reset() {
  this->player.resetPosition(this->level);
}
void Game::handleTick() {
  this->player.update(this->level);

  int offsetX = player.getX() - goalCharacterX;
  int offsetY = player.getY() - goalCharacterY;

  this->tiledDisplay.setOffset(offsetX, offsetY);
  
  int characterX = player.getX() - this->tiledDisplay.offsetX - 3;
  int characterY = player.getY() - this->tiledDisplay.offsetY - 4;

  this->tiledDisplay.setCharacterPosition(characterX, characterY);
  this->tiledDisplay.setCharacterFrame(this->player.animationFrame);

  this->tiledDisplay.draw();
}

