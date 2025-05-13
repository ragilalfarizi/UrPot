#pragma once

#include <Arduino.h>
#include <esp_err.h>

enum class GrowlightState {
  OFF = 0,
  ON,
};

class GrowlightController {
 public:
  GrowlightController();
  ~GrowlightController();

  esp_err_t begin();

 private:
};
