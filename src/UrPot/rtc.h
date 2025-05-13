#pragma once

#include <Arduino.h>
#include <esp_err.h>

class RTC{
 public:
  RTC();
  ~RTC();
  
  esp_err_t begin();

 private:
};
