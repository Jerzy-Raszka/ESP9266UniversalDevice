#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#include "CircleBreathing.h"
#include "Config.h"
#include "Display.h"

void printText(const char *textToPrint) {
  int16_t x1, y1;
  uint16_t width, height;
  display.setTextSize(1);
  display.getTextBounds(textToPrint, 0, 0, &x1, &y1, &width, &height);
  int16_t x = (SCREEN_WIDTH - width) / 2;
  display.setTextColor(WHITE);
  display.setCursor(x, 5);
  display.println(textToPrint);
}

void circleBreathing() {
  unsigned long start = 0;

  for (int i = 0; i <= RADIUS; i++) {
    display.clearDisplay();
    display.drawRect(((SCREEN_WIDTH / 2) - RADIUS - 1), RADIUS - 1,
                     ((RADIUS * 2) + 2), ((RADIUS * 2) + 2), WHITE);
    display.fillCircle((SCREEN_WIDTH / 2), (SCREEN_HEIGHT - RADIUS - 4), i,
                       WHITE);
    printText("Breath in");
    display.display();

    start = millis();
    while (millis() - start < 200) {
      yield();
    }
  }

  display.clearDisplay();
  printText("Hold");
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
    printText("Breath out");
    display.display();

    start = millis();
    while (millis() - start < 400) {
      yield();
    }
  }
}