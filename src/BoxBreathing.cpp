#include "BoxBreathing.h"
#include "Buttons.h"
#include "Config.h"
#include "Display.h"
#include "RenderCenteredText.h"
#include "TimeSet.h"

void drawBoxBreathingStep(int x, int y, const char *label) {
  display.clearDisplay();
  display.drawRect((SCREEN_WIDTH / 2) - RADIUS, RADIUS, RADIUS * 2, RADIUS * 2,
                   WHITE);
  display.fillCircle(x, y, 3, WHITE);
  renderCenteredText(label);
  display.display();
}

void boxBreathing() {
  unsigned long start = 0;
  unsigned long breathingStart = millis();
  unsigned long breathingTime = timeSet();

  int x = (SCREEN_WIDTH / 2) - RADIUS;
  int y = RADIUS;
  const uint8_t squareSize = RADIUS * 2;

  while (millis() - breathingStart < breathingTime) {
    for (int i = 0; i < squareSize; i++) {
      drawBoxBreathingStep(x + i, y, "Breath in");
      start = millis();
      while (millis() - start < 100) {
        yield();
      }
    }
    x += squareSize - 1;

    for (int i = 0; i < squareSize; i++) {
      drawBoxBreathingStep(x, y + i, "Hold");
      start = millis();
      while (millis() - start < 100) {
        yield();
      }
    }
    y += squareSize - 1;

    for (int i = 0; i < squareSize; i++) {
      drawBoxBreathingStep(x - i, y, "Breath out");
      start = millis();
      while (millis() - start < 100) {
        yield();
      }
    }
    x -= squareSize - 1;

    for (int i = 0; i < squareSize; i++) {
      drawBoxBreathingStep(x, y - i, "Hold");
      start = millis();
      while (millis() - start < 100) {
        yield();
      }
    }
    y -= squareSize - 1;

    yield();
  }
  display.clearDisplay();
  renderCenteredText("Finished!", MIDDLE_SCREEN, 2);
  display.display();
}