#include "rtc.h"

esp_err_t RTC::begin() {
  _rtc = new RTC_DS3231();
  if (!_rtc->begin(&_wire)) {
    return ESP_FAIL;
  }
  return ESP_OK;
}

esp_err_t RTC::getTimeDate(DateTime &time) {
  if (!_rtc) return ESP_FAIL;
  time = _rtc->now();
  return ESP_OK;
}

esp_err_t RTC::setTimeDate(const DateTime &dt) {
  if (!_rtc) return ESP_FAIL;
  _rtc->adjust(dt);
  return ESP_OK;
}
