#pragma once

#include <Arduino.h>
#include <esp_err.h>

class RelayController {
 public:
  RelayController();
  ~RelayController();

  esp_err_t begin();

 private:
};
