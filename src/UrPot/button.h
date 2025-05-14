#pragma once

#include <Arduino.h>
#include <esp_err.h>

typedef void (*ButtonCallback)();

class Button {
 public:
  Button(uint8_t pin);

  esp_err_t begin();
  void      update();                 // Call this in loop/task
  void      onClick(ButtonCallback);  // Register callback
  bool      isPressed();

 private:
  uint8_t        _pin;
  bool           _lastState;
  ButtonCallback _callback;
};
