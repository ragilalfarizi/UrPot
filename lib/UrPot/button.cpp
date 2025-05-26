#include "button.h"

const char *Button::TAG = "BUTTON";

Button::Button(uint8_t pin)
    : _pin(pin), _lastState(false), _callback(nullptr) {}

esp_err_t Button::begin() {
  pinMode(_pin, INPUT);  // Assuming external pull-down resistor
  ESP_LOGD(TAG, "Button initialized on pin %d", _pin);
  return ESP_OK;
}

void Button::onClick(ButtonCallback cb) { _callback = cb; }

void Button::update() {
  bool current = digitalRead(_pin);
  ESP_LOGD(TAG, "Button state: %s", current ? "HIGH" : "LOW");

  // Detect rising edge: LOW -> HIGH (press)
  if (current && !_lastState && _callback) {
    _callback();
  }

  _lastState = current;
}

bool Button::isPressed() { return digitalRead(_pin); }
