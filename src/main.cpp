#include <Arduino.h>
#include <Wire.h>

#include "BoxBreathing.h"
#include "Buttons.h"
#include "CircleBreathing.h"
#include "Config.h"
#include "Display.h"
#include "GymTimer.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(ACCEPT, INPUT_PULLUP);
  pinMode(BACK, INPUT_PULLUP);
  attachInterrupt(RIGHT, onRight, FALLING);
  attachInterrupt(LEFT, onLeft, FALLING);
  attachInterrupt(ACCEPT, onAccept, FALLING);
  attachInterrupt(BACK, onBack, FALLING);

  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) {
    }
  }
  delay(2000);
  display.clearDisplay();
}

void loop() {
  // circleBreathing();
  // boxBreathing();
  // gymTimer(1, 30);
  if (rightPressed) {
    Serial.println("Right");
    rightPressed = false;
  }
  if (leftPressed) {
    Serial.println("Left");
    leftPressed = false;
  }
  if (acceptPressed) {
    Serial.println("Accept");
    acceptPressed = false;
  }
  if (backPressed) {
    Serial.println("Back");
    backPressed = false;
  }
}
