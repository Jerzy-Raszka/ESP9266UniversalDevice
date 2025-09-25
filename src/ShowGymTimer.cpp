#include "ShowGymTimer.h"
#include "Config.h"
#include "Display.h"
#include "RenderCenteredText.h"

void showGymTimer() {
  display.clearDisplay();
  renderCenteredText("Timer");
  display.drawCircle((SCREEN_WIDTH / 2), (SCREEN_HEIGHT - RADIUS - 4), RADIUS,
                     SH110X_WHITE);
  display.drawLine((SCREEN_WIDTH / 2), (SCREEN_HEIGHT - RADIUS - 4),
                   ((SCREEN_WIDTH / 2) + RADIUS - 4),
                   (SCREEN_HEIGHT - RADIUS - 4), SH110X_WHITE);
  display.drawLine((SCREEN_WIDTH / 2), (SCREEN_HEIGHT - RADIUS - 4),
                   (SCREEN_WIDTH / 2), (SCREEN_HEIGHT - (2 * RADIUS)),
                   SH110X_WHITE);
  display.display();
}