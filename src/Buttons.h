#pragma once
#include <Arduino.h>

extern volatile bool rightPressed;
extern volatile bool leftPressed;
extern volatile bool acceptPressed;
extern volatile bool backPressed;

void IRAM_ATTR onRight();
void IRAM_ATTR onLeft();
void IRAM_ATTR onAccept();
void IRAM_ATTR onBack();

inline bool checkBackPressed() {
  if (backPressed) {
    acceptPressed = false;
    backPressed = false;
    return true;
  }
  return false;
}