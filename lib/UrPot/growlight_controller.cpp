#include "growlight_controller.h"

const char *GrowlightController::TAG = "GROWLIGHT";

GrowlightController::GrowlightController(uint8_t pin)
    : _pin(pin), _state(GrowlightState::OFF) {}

esp_err_t GrowlightController::begin() {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  _state = GrowlightState::OFF;

  return ESP_OK;
}

esp_err_t GrowlightController::on() {
  ESP_LOGD(TAG, "Turning growlight ON");

  if (_state == GrowlightState::ON) {
    return ESP_OK;  // Already ON
  }

  digitalWrite(_pin, HIGH);
  _state = GrowlightState::ON;
  return ESP_OK;
}

esp_err_t GrowlightController::off() {
  ESP_LOGD(TAG, "Turning growlight ON");

  if (_state == GrowlightState::OFF) {
    return ESP_OK;  // Already OFF
  }

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
