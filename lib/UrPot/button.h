#pragma once

#include <Arduino.h>
#include <esp_err.h>

#include "defs.h"

typedef void (*ButtonCallback)();

class Button {
 public:
  Button(uint8_t pin);

  esp_err_t begin();
  void      update();                 // Call this in loop/task
  void      onClick(ButtonCallback);  // Register callback
  bool      isPressed();

  static const char *TAG;

 private:
  uint8_t        _pin;
  bool           _lastState;
  ButtonCallback _callback;
};
