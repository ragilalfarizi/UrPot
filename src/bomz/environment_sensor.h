
#pragma once

#include <Arduino.h>
#include <esp_err.h>

class EnvironmentSensor {
 public:
  EnvironmentSensor();
  ~EnvironmentSensor();

  esp_err_t begin();

 private:
};
