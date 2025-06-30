#pragma once
#include <Arduino.h>

extern volatile bool rightPressed;
extern volatile bool leftPressed;
extern volatile bool acceptPressed;

void IRAM_ATTR onRight();
void IRAM_ATTR onLeft();
void IRAM_ATTR onAccept();
