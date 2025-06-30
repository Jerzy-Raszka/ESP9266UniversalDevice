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
// TODO: Time select before Circle breathing with minutes
// TODO: Minute select -> accept -> second select -> accept -> start
void loop() { boxBreathing(); }
