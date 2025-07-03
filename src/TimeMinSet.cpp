#include "Buttons.h"
#include "Config.h"
#include "Display.h"
#include "RenderCenteredText.h"

unsigned long timeMinSet() {
  unsigned long breathingTime = 5 * 60;
  static int8_t lastMin = 5;
  int8_t min = lastMin;
  String timeStr = String(min) + "min";

  while (!acceptPressed) {
    display.clearDisplay();
    renderCenteredText("Input time:");
    timeStr = String(min) + " min";
    renderCenteredText(timeStr.c_str(), MIDDLE_SCREEN, 2);
    if (rightPressed) {
      min = (min == 60) ? 1 : min + 1;
      rightPressed = false;
    }
    if (leftPressed) {
      min = (min == 1) ? 60 : min - 1;
      leftPressed = false;
    }
    display.display();
    yield();
  }

  acceptPressed = false;
  lastMin = min;
  breathingTime = min * 60 * 1000;
  return breathingTime;
}