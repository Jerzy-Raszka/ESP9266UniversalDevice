#include "CircleBreathing.h"
#include "Buttons.h"
#include "Config.h"
#include "Display.h"
#include "RenderCenteredText.h"
#include "TimeMinSet.h"

const unsigned long INHALE_STEP_MS = 200;
const unsigned long HOLD_MS = 7000;
const unsigned long EXHALE_STEP_MS = 400;
const int CIRCLE_CENTER_X = SCREEN_WIDTH / 2;
const int CIRCLE_CENTER_Y = SCREEN_HEIGHT - RADIUS - 4;

void drawBreathingCircle(int radius, const char *label) {
  display.clearDisplay();
  display.drawRect(CIRCLE_CENTER_X - RADIUS - 1, RADIUS - 1, (RADIUS * 2) + 2,
                   (RADIUS * 2) + 2, SH110X_WHITE);
  display.fillCircle(CIRCLE_CENTER_X, CIRCLE_CENTER_Y, radius, SH110X_WHITE);
  renderCenteredText(label);
  display.display();
}

void circleBreathing() {
  static int8_t lastCircleMin = 5;
  unsigned long breathingStart = millis();
  unsigned long breathingTime = timeMinSet(lastCircleMin);

  while (millis() - breathingStart < breathingTime) {
    for (int i = 0; i <= RADIUS; i++) {
      if (checkBackPressed()) {
        return;
      }
      drawBreathingCircle(i, "Breath in");
      unsigned long start = millis();
      while (millis() - start < INHALE_STEP_MS) {
        if (backPressed) {
          acceptPressed = false;
          backPressed = false;
          return;
        }
        yield();
      }
    }

    drawBreathingCircle(RADIUS, "Hold");
    unsigned long holdStart = millis();
    while (millis() - holdStart < HOLD_MS) {
      if (checkBackPressed()) {
        return;
      }
      yield();
    }

    for (int i = RADIUS; i > 0; i--) {
      if (checkBackPressed()) {
        return;
      }
      drawBreathingCircle(i, "Breath out");
      unsigned long start = millis();
      while (millis() - start < EXHALE_STEP_MS) {
        if (backPressed) {
          acceptPressed = false;
          backPressed = false;
          return;
        }
        yield();
      }
    }
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
    circleBreathing();
    acceptPressed = false;
  }
}