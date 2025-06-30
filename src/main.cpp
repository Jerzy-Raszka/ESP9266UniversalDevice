#include <Arduino.h>
#include <Wire.h>

#include "BoxBreathing.h"
#include "Buttons.h"
#include "CircleBreathing.h"
#include "Config.h"
#include "Display.h"
#include "GymTimer.h"
#include "ShowBoxBreathing.h"
#include "ShowCircleBreathing.h"
#include "ShowGymTimer.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int8_t task = 0;
boolean taskChanged = true;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(ACCEPT, INPUT_PULLUP);
  attachInterrupt(RIGHT, onRight, FALLING);
  attachInterrupt(LEFT, onLeft, FALLING);
  attachInterrupt(ACCEPT, onAccept, FALLING);

  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) {
    }
  }
  delay(2000);
  display.clearDisplay();
}

// TODO: Main screen right/left -> accept for mode
void loop() {
  while (!acceptPressed) {
    if (rightPressed) {
      taskChanged = true;
      if (task == 2) {
        task = 0;
      } else {
        task += 1;
      }
      rightPressed = false;
    }

    if (leftPressed) {
      taskChanged = true;
      if (task == 0) {
        task = 2;
      } else {
        task -= 1;
      }
      leftPressed = false;
    }

    if (taskChanged) {
      switch (task) {
      case 0:
        showGymTimer();
        taskChanged = false;
        break;
      case 1:
        showBoxBreathing();
        taskChanged = false;
        break;
      case 2:
        showCircleBreathing();
        taskChanged = false;
        break;
      }
    }
    yield();
  }

  acceptPressed = false;

  switch (task) {
  case 0:
    gymTimer(1, 30); // TODO: add time select for gym timer
    break;
  case 1:
    boxBreathing();
    break;
  case 2:
    circleBreathing();
    break;
  }
}
