#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>
#include <esp_err.h>

#define I2C_ADDR_DISPLAY      0x57
#define PIN_SDA_DISPLAY       0x02
#define PIN_SCl_DISPLAY       0x03
#define DISPLAY_SCREEN_WIDTH  128
#define DISPLAY_SCREEN_HEIGHT 64

class Display {
 public:
  Display(TwoWire &wire, uint8_t address = I2C_ADDR_DISPLAY);
  ~Display();

  esp_err_t begin();
  esp_err_t print(const String &text, int16_t x = 0, int16_t y = 0,
                  bool clear = true);
  esp_err_t clear();

 private:
  Adafruit_SSD1306 *_oled = nullptr;
  TwoWire          &_wire;
  uint8_t           _address;
};
