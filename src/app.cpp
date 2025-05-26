#include "app.h"

const char* TAG = "URPOT";

UrPot::UrPot() {}

UrPot::~UrPot() {}

esp_err_t UrPot::begin() {
  esp_err_t ret = ESP_OK;

  Serial.begin(115200);

  // RTC init
  // _rtc = new RTC();
  // if (_rtc == nullptr) {
  //   ESP_LOGE(TAG, "RTC is Failed to Initialized.");
  //   return ESP_FAIL;
  // }
  // ret = _rtc->begin();

  // Growlight Init
  _light = new GrowlightController(8);
  if (_light == nullptr) {
    ESP_LOGE(TAG, "Growlight is Failed to Initialized.");
    return ESP_FAIL;
  }
  ret = _light->begin();

  // BLE init
  // _ble = new BTAudio();
  // if (_ble == nullptr) {
  //   ESP_LOGE(TAG, "BLE is Failed to Initialized.");
  //   return ESP_FAIL;
  // }
  // ret = _ble->begin();

  return ret;
}
