#pragma once

#include <Arduino.h>
#include <RTClib.h>
#include <Wire.h>
#include <esp_err.h>

#define I2C_ADDR_RTC 0x56

class RTC {
 public:
  RTC(TwoWire &wire = Wire) : _wire(wire) {}
  ~RTC() {}

  esp_err_t begin();
  esp_err_t getTimeDate(DateTime &time);
  esp_err_t setTimeDate(const DateTime &dt);

 private:
  TwoWire    &_wire;
  RTC_DS3231 *_rtc = nullptr;
};
