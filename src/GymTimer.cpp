#include "GymTimer.h"
#include "Config.h"
#include "Display.h"
#include "RenderCenteredText.h"

void gymTimer(int min, int sec) {
  unsigned long start = 0;
  String timeStr = String(min) + ":" + String(sec);

  for (int i = min; i >= 0; i--) {
    for (int j = sec; j >= 0; j--) {
      display.clearDisplay();
      renderCenteredText("Time left:");
      if (j < 10) {
        timeStr = String(i) + ":0" + String(j);
      } else {
        timeStr = String(i) + ":" + String(j);
      }
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
}