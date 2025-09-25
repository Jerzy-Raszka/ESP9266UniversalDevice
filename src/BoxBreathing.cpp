#include "BoxBreathing.h"
#include "Buttons.h"
#include "Config.h"
#include "Display.h"
#include "RenderCenteredText.h"
#include "TimeMinSet.h"

void drawBoxBreathingStep(int x, int y, const char *label) {
  display.clearDisplay();
  display.drawRect((SCREEN_WIDTH / 2) - RADIUS, RADIUS, RADIUS * 2, RADIUS * 2,
                   SH110X_WHITE);
  display.fillCircle(x, y, 3, SH110X_WHITE);
  renderCenteredText(label);
  display.display();
}

void boxBreathing() {
  static int8_t lastBoxMin = 5;
  unsigned long start = 0;
  unsigned long breathingStart = millis();
  unsigned long breathingTime = timeMinSet(lastBoxMin);

  int x = (SCREEN_WIDTH / 2) - RADIUS;
  int y = RADIUS;
  const uint8_t squareSize = RADIUS * 2;

  while (millis() - breathingStart < breathingTime) {
    for (int i = 0; i < squareSize; i++) {
      if (checkBackPressed()) {
        return;
      }
      drawBoxBreathingStep(x + i, y, "Breath in");
      start = millis();
      while (millis() - start < 100) {
        if (backPressed) {
          acceptPressed = false;
          backPressed = false;
          return;
        }
        yield();
      }
    }
    x += squareSize - 1;

    for (int i = 0; i < squareSize; i++) {
      if (checkBackPressed()) {
        return;
      }
      drawBoxBreathingStep(x, y + i, "Hold");
      start = millis();
      while (millis() - start < 100) {
        if (backPressed) {
          acceptPressed = false;
          backPressed = false;
          return;
        }
        yield();
      }
    }
    y += squareSize - 1;

    for (int i = 0; i < squareSize; i++) {
      if (checkBackPressed()) {
        return;
      }
      drawBoxBreathingStep(x - i, y, "Breath out");
      start = millis();
      while (millis() - start < 100) {
        if (backPressed) {
          acceptPressed = false;
          backPressed = false;
          return;
        }
        yield();
      }
    }
    x -= squareSize - 1;

    for (int i = 0; i < squareSize; i++) {
      if (checkBackPressed()) {
        return;
      }
      drawBoxBreathingStep(x, y - i, "Hold");
      start = millis();
      while (millis() - start < 100) {
        if (backPressed) {
          acceptPressed = false;
          backPressed = false;
          return;
        }
        yield();
      }
    }
    y -= squareSize - 1;

    yield();
  }
  display.clearDisplay();
  renderCenteredText("Finished!");
  renderCenteredText("Press accept to restart task", MIDDLE_SCREEN);
  display.display();

  while (acceptPressed) {
    if (backPressed) {
      acceptPressed = false;
      backPressed = false;
      return;
    }
    boxBreathing();
    acceptPressed = false;
  }
}