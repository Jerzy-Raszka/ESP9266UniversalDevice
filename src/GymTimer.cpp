#include "GymTimer.h"
#include "Buttons.h"
#include "Config.h"
#include "Display.h"
#include "RenderCenteredText.h"
#include "TimeMinSecSet.h"
#include "TimeMinSecStruct.h"


void gymTimer() {
  unsigned long start = 0;
  timeMinSecStruct timeSet = timeMinSecSet();
  u_int8_t min = timeSet.min;
  u_int8_t sec = timeSet.sec;
  String timeStr = String(min) + ":" + String(sec);

  for (int i = min; i >= 0; i--) {
    for (int j = sec; j >= 0; j--) {
      display.clearDisplay();
      renderCenteredText("Time left:");
      timeStr = j < 10 ? (String(i) + ":0" + String(j))
                       : (String(i) + ":" + String(j));
      if (j < 5 && i == 0) {
        digitalWrite(BUZZER, HIGH);
        start = millis();
        while (millis() - start < 250) {
          yield();
        }
        digitalWrite(BUZZER, LOW);
      }
      renderCenteredText(timeStr.c_str(), MIDDLE_SCREEN, 2);
      display.display();
      start = millis();
      while (millis() - start < 1000) {
        yield();
      }
    }
    sec = 59;
  }
  digitalWrite(BUZZER, HIGH);
  start = millis();
  while (millis() - start < 1000) {
    yield();
  }
  digitalWrite(BUZZER, LOW);
  display.clearDisplay();
  renderCenteredText("Finished!");
  renderCenteredText("Press accept to restart task", MIDDLE_SCREEN);
  display.display();

  while (acceptPressed) {
    gymTimer();
    acceptPressed = false;
  }
}