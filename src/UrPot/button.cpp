#include "button.h"

Button::Button(uint8_t pin)
    : _pin(pin), _lastState(false), _callback(nullptr) {}

esp_err_t Button::begin() {
  pinMode(_pin, INPUT);  // Assuming external pull-down resistor
  return ESP_OK;
}

void Button::onClick(ButtonCallback cb) { _callback = cb; }

void Button::update() {
  bool current = digitalRead(_pin);

  // Detect rising edge: LOW -> HIGH (press)
  if (current && !_lastState && _callback) {
    _callback();
  }

  _lastState = current;
}

bool Button::isPressed() { return digitalRead(_pin); }
