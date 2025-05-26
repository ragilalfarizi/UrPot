#include "rtc.h"

const char *RTC::TAG = "RTC";

RTC::~RTC() {
  if (_rtc) {
    delete _rtc;
    _rtc = nullptr;
  }
}

esp_err_t RTC::begin() {
  _rtc = new RTC_DS3231();

  if (_rtc == nullptr) {
    ESP_LOGE(TAG, "RTC is Failed to be created.");
    return ESP_FAIL;
  }

  if (!_rtc->begin(&_wire)) {
    ESP_LOGE(TAG, "RTC is Failed to Initialized.");
    delete _rtc;
    _rtc = nullptr;
    return ESP_FAIL;
  }

  ESP_LOGI(TAG, "RTC Initialized.");

  if (_rtc->lostPower()) {
    ESP_LOGI(TAG, "RTC lost power, setting the time.");
    // Set the date and time to a known value
    DateTime now = DateTime(F(__DATE__), F(__TIME__));
    _rtc->adjust(now);

    // DateTime custom_time(2025, 5, 26, 23, 10, 0);
    // _rtc->adjust(custom_time);
  }

  // NOTE: SET THE TIME HERE
  // DateTime custom_time(2025, 5, 26, 23, 10, 0);
  // _rtc->adjust(custom_time);

  return ESP_OK;
}

esp_err_t RTC::getTimeDate(DateTime &time) {
  if (!_rtc) return ESP_FAIL;
  time = _rtc->now();
  return ESP_OK;
}

esp_err_t RTC::setTimeDate(const DateTime &dt) {
  if (!_rtc) return ESP_FAIL;

  if (dt.year() < 2000 || dt.year() > 2099) {
    ESP_LOGE(TAG, "Invalid year: %d", dt.year());
    return ESP_ERR_INVALID_ARG;
  }

  ESP_LOGI(TAG, "RTC set time: %04d-%02d-%02d %02d:%02d:%02d", dt.year(),
           dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());
  _rtc->adjust(dt);

  return ESP_OK;
}
