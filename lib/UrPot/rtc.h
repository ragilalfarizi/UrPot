#pragma once

#include <Arduino.h>
#include <RTClib.h>
#include <Wire.h>
#include <esp_err.h>

#include "defs.h"

enum class RTCState {
  OUTSIDE_SCHEDULE,
  INSIDE_SCHEDULE,
  OFF,
};

class RTC {
 public:
  RTC(TwoWire &wire) : _wire(wire) {}
  ~RTC();

  esp_err_t begin();
  esp_err_t getTimeDate(DateTime &time);
  esp_err_t setTimeDate(const DateTime &dt);

  static const char *TAG;

 private:
  TwoWire    &_wire;
  RTC_DS3231 *_rtc = nullptr;
};
