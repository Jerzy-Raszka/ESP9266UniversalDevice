#include "CircleBreathing.h"
#include "Config.h"
#include "Display.h"
#include "RenderCenteredText.h"

void circleBreathing() {
  unsigned long start = 0;

  for (int i = 0; i <= RADIUS; i++) {
    display.clearDisplay();
    display.drawRect(((SCREEN_WIDTH / 2) - RADIUS - 1), RADIUS - 1,
                     ((RADIUS * 2) + 2), ((RADIUS * 2) + 2), WHITE);
    display.fillCircle((SCREEN_WIDTH / 2), (SCREEN_HEIGHT - RADIUS - 4), i,
                       WHITE);
    renderCenteredText("Breath in");
    display.display();

    start = millis();
    while (millis() - start < 200) {
      yield();
    }
  }

  display.clearDisplay();
  renderCenteredText("Hold");
  display.drawRect(((SCREEN_WIDTH / 2) - RADIUS - 1), RADIUS - 1,
                   ((RADIUS * 2) + 2), ((RADIUS * 2) + 2), WHITE);
  display.fillCircle((SCREEN_WIDTH / 2), (SCREEN_HEIGHT - RADIUS - 4), 20,
                     WHITE);
  display.display();

  start = millis();
  while (millis() - start < 7000) {
    yield();
  }

  for (int j = RADIUS; j > 0; j--) {
    display.clearDisplay();
    display.drawRect(((SCREEN_WIDTH / 2) - RADIUS - 1), RADIUS - 1,
                     ((RADIUS * 2) + 2), ((RADIUS * 2) + 2), WHITE);
    display.fillCircle((SCREEN_WIDTH / 2), (SCREEN_HEIGHT - RADIUS - 4), j,
                       WHITE);
    renderCenteredText("Breath out");
    display.display();

    start = millis();
    while (millis() - start < 400) {
      yield();
    }
  }
}