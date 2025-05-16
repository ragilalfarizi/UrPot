#include "growlight_controller.h"

GrowlightController::GrowlightController(uint8_t pin)
    : _pin(pin), _state(GrowlightState::OFF) {}

esp_err_t GrowlightController::begin() {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  return ESP_OK;
}

esp_err_t GrowlightController::on() {
  digitalWrite(_pin, HIGH);
  _state = GrowlightState::ON;
  return ESP_OK;
}

esp_err_t GrowlightController::off() {
  digitalWrite(_pin, LOW);
  _state = GrowlightState::OFF;
  return ESP_OK;
}

esp_err_t GrowlightController::toggle() {
  if (_state == GrowlightState::OFF) {
    on();
  } else {
    off();
  }
  return ESP_OK;
}

GrowlightState GrowlightController::getState() { return _state; }
