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

// TODO: 60 -> 1, 1->60 in breathings
// TODO: 59 -> 0 in seconds in timer
// TODO: ability to restart task after finishing them from setting timer again
// with the same time as in previous task
// TODO: move menu and task option to their own functions maybe?

void loop() {
  while (!acceptPressed) {
    if (rightPressed) {
      task = (task == 2) ? 0 : task + 1;
      taskChanged = true;
      rightPressed = false;
    }

    if (leftPressed) {
      taskChanged = true;
      task = (task == 0) ? 2 : task - 1;
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
    gymTimer();
    break;
  case 1:
    boxBreathing();
    break;
  case 2:
    circleBreathing();
    break;
  }
}
