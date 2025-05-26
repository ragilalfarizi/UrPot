#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>
#include <esp_err.h>

#include "defs.h"

class Display {
 public:
  Display(TwoWire &wire, uint8_t address = DISPLAY_ADDRESS);
  ~Display();

  esp_err_t begin();
  esp_err_t print(const String &text, int16_t x = 0, int16_t y = 0,
                  bool clear = true);
  esp_err_t clear();

  static const char *TAG;

 private:
  Adafruit_SSD1306 *_oled = nullptr;
  TwoWire          &_wire;
  uint8_t           _address;
};
