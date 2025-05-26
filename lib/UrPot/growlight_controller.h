#pragma once

#include <Arduino.h>
#include <esp_err.h>

#include "defs.h"

enum class GrowlightState {
  OFF,
  ON,
};

class GrowlightController {
 public:
  GrowlightController(uint8_t pin);

  esp_err_t      begin();
  esp_err_t      on();
  esp_err_t      off();
  esp_err_t      toggle();
  GrowlightState getState();

  static const char *TAG;

 private:
  uint8_t        _pin;
  GrowlightState _state;
};
