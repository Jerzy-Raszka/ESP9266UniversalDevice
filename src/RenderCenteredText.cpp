#include "Config.h"
#include "Display.h"

void renderCenteredText(const char *textToPrint) {
  int16_t x1, y1;
  uint16_t width, height;
  display.setTextSize(1);
  display.getTextBounds(textToPrint, 0, 0, &x1, &y1, &width, &height);
  int16_t x = (SCREEN_WIDTH - width) / 2;
  display.setTextColor(WHITE);
  display.setCursor(x, 5);
  display.println(textToPrint);
}