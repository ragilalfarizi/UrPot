#pragma once

#include <Arduino.h>
#include <esp_err.h>

enum class BTState {
  DISCONNECTED = 0,
  CONNECTED,
};

class BTAudio {
 public:
  BTAudio();
  ~BTAudio();

  esp_err_t begin();

 private:
};
