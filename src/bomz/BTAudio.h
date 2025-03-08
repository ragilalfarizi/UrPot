#pragma once

#include <Arduino.h>
#include <esp_err.h>

class BTAudio {
 public:
  BTAudio();
  ~BTAudio();

  esp_err_t begin();

 private:
};
