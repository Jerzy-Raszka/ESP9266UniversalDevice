#include "Config.h"
#include "Display.h"
#include "RenderCenteredText.h"

void boxBreathing() {
  unsigned long start = 0;
  int8_t x = ((SCREEN_WIDTH / 2) - RADIUS);
  int8_t xRect = ((SCREEN_WIDTH / 2) - RADIUS);
  int8_t y = RADIUS;
  int8_t yRect = RADIUS;
  u_int8_t squareSize = ((RADIUS * 2));

  for (int i = 0; i < squareSize; i++) {
    display.clearDisplay();
    display.drawRect(xRect, yRect, squareSize, squareSize, WHITE);
    display.fillCircle(x + i, y, 4, WHITE);
    renderCenteredText("Breath in");
    display.display();
    start = millis();
    while (millis() - start < 100) {
      yield();
    }
  }
  x += squareSize - 1;

  for (int i = 0; i < squareSize; i++) {
    display.clearDisplay();
    display.drawRect(xRect, yRect, squareSize, squareSize, WHITE);
    display.fillCircle(x, y + i, 4, WHITE);
    renderCenteredText("Hold");
    display.display();
    start = millis();
    while (millis() - start < 100) {
      yield();
    }
  }
  y += squareSize - 1;

  for (int i = 0; i < squareSize; i++) {
    display.clearDisplay();
    display.drawRect(xRect, yRect, squareSize, squareSize, WHITE);
    display.fillCircle(x - i, y, 4, WHITE);
    renderCenteredText("Breath out");
    display.display();
    start = millis();
    while (millis() - start < 100) {
      yield();
    }
  }
  x -= squareSize - 1;

  for (int i = 0; i < squareSize; i++) {
    display.clearDisplay();
    display.drawRect(xRect, yRect, squareSize, squareSize, WHITE);
    display.fillCircle(x, y - i, 4, WHITE);
    renderCenteredText("Hold");
    display.display();
    start = millis();
    while (millis() - start < 100) {
      yield();
    }
  }
  y -= squareSize;
}
