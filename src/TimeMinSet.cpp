#include "Buttons.h"
#include "Config.h"
#include "Display.h"
#include "RenderCenteredText.h"

unsigned long timeMinSet() {
  unsigned long breathingTime = 5 * 60;
  int8_t min = 5;
  String timeStr = String(min) + "min";

  while (!acceptPressed) {
    display.clearDisplay();
    renderCenteredText("Input time:");
    timeStr = String(min) + " min";
    renderCenteredText(timeStr.c_str(), MIDDLE_SCREEN, 2);
    if (rightPressed) {
      min = (min + 1) % 61;
      rightPressed = false;
    }
    if (leftPressed) {
      min = (min == 0) ? 60 : min - 1;
      leftPressed = false;
    }
    display.display();
    yield();
  }

  acceptPressed = false;
  breathingTime = min * 60 * 1000;
  return breathingTime;
}