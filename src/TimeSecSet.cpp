#include "Buttons.h"
#include "Config.h"
#include "Display.h"
#include "RenderCenteredText.h"
#include "TimeMinSec.h"

timeMinSec timeSecSet() {
  bool blinkOn = false;
  boolean setingSec = true;
  boolean setingMin = false;
  u_int8_t min = 1;
  u_int8_t sec = 45;
  timeMinSec setTime = {0, 0};
  String timeStr = " " + String(min) + ":" + String(sec);

  while (setingSec) {
    display.clearDisplay();
    renderCenteredText("Input seconds");
    blinkOn = (millis() / 500) % 2 == 0;
    if (blinkOn) {
      if (sec < 10) {
        timeStr = " " + String(min) + ":0" + String(sec);
      } else {
        timeStr = " " + String(min) + ":" + String(sec);
      }
    } else {
      timeStr = " " + String(min) + ":  ";
    }
    renderCenteredText(timeStr.c_str(), MIDDLE_SCREEN, 2);
    if (rightPressed) {
      if (sec + 1 == 60) {
        sec = 0;
      } else {
        sec++;
      }
      rightPressed = false;
    }
    if (leftPressed) {
      if (sec - 1 == 0) {
        sec = 60;
      } else {
        sec--;
      }
      leftPressed = false;
    }
    if (acceptPressed) {
      setingSec = false;
      setingMin = true;
      acceptPressed = false;
    }
    display.display();
    yield();
  }

  while (setingMin) {
    display.clearDisplay();
    renderCenteredText("Input minutes");
    blinkOn = (millis() / 500) % 2 == 0;
    if (blinkOn) {
      if (min < 10) {
        if (sec < 10) {
          timeStr = " " + String(min) + ":0" + String(sec);
        } else {
          timeStr = " " + String(min) + ":" + String(sec);
        }
      } else {
        if (sec < 10) {
          timeStr = String(min) + ":0" + String(sec);
        } else {
          timeStr = String(min) + ":" + String(sec);
        }
      }
    } else {
      if (min < 10) {
        if (sec < 10) {
          timeStr = "  :0" + String(sec);
        } else {
          timeStr = "  :" + String(sec);
        }
      } else {
        if (sec < 10) {
          timeStr = "  :0" + String(sec);
        } else {
          timeStr = "  :" + String(sec);
        }
      }
    }
    renderCenteredText(timeStr.c_str(), MIDDLE_SCREEN, 2);
    if (rightPressed) {
      if (min == 60) {
        min = 0;
      } else {
        min++;
      }
      rightPressed = false;
    }
    if (leftPressed) {
      if (min == 0) {
        min = 60;
      } else {
        min--;
      }
      leftPressed = false;
    }
    if (acceptPressed) {
      setingSec = false;
      setingMin = false;
      acceptPressed = false;
      setTime = {min, sec};
      return setTime;
    }
    display.display();
    yield();
  }
  return setTime;
}
