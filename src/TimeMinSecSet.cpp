#include "Buttons.h"
#include "Config.h"
#include "Display.h"
#include "RenderCenteredText.h"
#include "TimeMinSecStruct.h"

String formatTime(uint8_t min, uint8_t sec, bool blink, bool blinkSec) {
  String minStr = (min < 10) ? " " + String(min) : String(min);
  String secStr = (sec < 10) ? "0" + String(sec) : String(sec);

  if (blink) {
    if (blinkSec) {
      secStr = "  ";
    } else {
      minStr = "  ";
    }
  }
  return minStr + ":" + secStr;
}

timeMinSecStruct timeMinSecSet() {
  bool blinkOn = false;
  bool settingSec = true;
  bool settingMin = false;
  static uint8_t min = 1;
  static uint8_t sec = 45;
  timeMinSecStruct setTime = {0, 0};

  while (settingSec) {
    display.clearDisplay();
    renderCenteredText("Input seconds");
    blinkOn = (millis() / 500) % 2 == 0;
    String timeStr = formatTime(min, sec, blinkOn, true);
    renderCenteredText(timeStr.c_str(), MIDDLE_SCREEN, 2);

    if (rightPressed) {
      sec = (sec == 59) ? 0 : sec + 1;
      rightPressed = false;
    }
    if (leftPressed) {
      sec = (sec == 0) ? 59 : sec - 1;
      leftPressed = false;
    }
    if (acceptPressed) {
      settingSec = false;
      settingMin = true;
      acceptPressed = false;
    }
    display.display();
    yield();
  }

  while (settingMin) {
    display.clearDisplay();
    renderCenteredText("Input minutes");
    blinkOn = (millis() / 500) % 2 == 0;
    String timeStr = formatTime(min, sec, blinkOn, false);
    renderCenteredText(timeStr.c_str(), MIDDLE_SCREEN, 2);

    if (rightPressed) {
      min = (min + 1) % 61;
      rightPressed = false;
    }
    if (leftPressed) {
      min = (min == 0) ? 60 : min - 1;
      leftPressed = false;
    }
    if (acceptPressed) {
      settingMin = false;
      acceptPressed = false;
      setTime = {min, sec};
      return setTime;
    }
    display.display();
    yield();
  }
  return setTime;
}