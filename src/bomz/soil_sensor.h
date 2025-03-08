
#pragma once

#include <Arduino.h>
#include <esp_err.h>

class SoilSensor {
 public:
  SoilSensor();
  ~SoilSensor();

  esp_err_t begin();

 private:
};
