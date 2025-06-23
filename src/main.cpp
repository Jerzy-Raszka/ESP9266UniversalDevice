#include <Arduino.h>
#include <Wire.h>

#include "BoxBreathing.h"
#include "CircleBreathing.h"
#include "Config.h"
#include "Display.h"


#define BUZZER D5

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);

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
  boxBreathing();
}
