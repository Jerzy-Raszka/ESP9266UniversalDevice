#include "Config.h"
#include "Display.h"

void renderCenteredText(const char *textToPrint, int textHeight, int textSize) {
  int16_t x1, y1;
  uint16_t width, height;
  display.setTextSize(textSize);
  display.getTextBounds(textToPrint, 0, 0, &x1, &y1, &width, &height);
  int16_t x = (SCREEN_WIDTH - width) / 2;
  display.setTextColor(WHITE);
  display.setCursor(x, textHeight);
  display.println(textToPrint);
}