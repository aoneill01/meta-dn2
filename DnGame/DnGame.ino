#include <Gamebuino-Meta.h>
#include <utility/Adafruit_ZeroDMA.h>
#include "Game.h"

Game game;

void setup() {
  gb.begin();
  gb.display.init(0, 0, ColorMode::rgb565);
  gb.setFrameRate(40);
  
  SerialUSB.begin(9600);

  game.reset();
}

void loop() {
  while (!gb.update());

  game.handleTick();

  if (gb.frameCount % 25 == 0) SerialUSB.printf("CPU: %i\n", gb.getCpuLoad());
}


