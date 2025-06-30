#include "Buttons.h"
#include "Config.h"

unsigned long button_time = 0;
unsigned long last_button_time = 0;

volatile bool rightPressed = false;
volatile bool leftPressed = false;
volatile bool acceptPressed = false;

void IRAM_ATTR onRight() {
  button_time = millis();
  if (button_time - last_button_time > 250) {
    rightPressed = true;
    last_button_time = button_time;
  }
}

void IRAM_ATTR onLeft() {
  button_time = millis();
  if (button_time - last_button_time > 250) {
    leftPressed = true;
    last_button_time = button_time;
  }
}

void IRAM_ATTR onAccept() {
  button_time = millis();
  if (button_time - last_button_time > 250) {
    acceptPressed = true;
    last_button_time = button_time;
  }
}
