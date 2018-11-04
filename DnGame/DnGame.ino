// #define SCREEN_RECORD true

#include <Gamebuino-Meta.h>
#include "Game.h"

Game game;

void setup() {
  gb.begin();
  gb.display.init(0, 0, ColorMode::rgb565);
  gb.setFrameRate(40);
  
  SerialUSB.begin(9600);

  game.loadLevel();
}

void loop() {
  while (!gb.update());

  game.handleTick();
  
#ifndef SCREEN_RECORD
  if (gb.frameCount % 25 == 0) SerialUSB.printf("CPU: %i\n", gb.getCpuLoad());
#endif
}
