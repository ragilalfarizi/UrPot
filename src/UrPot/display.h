#pragma once

#include <Arduino.h>
#include <esp_err.h>

class Display{
 public:
  Display();
  ~Display();
  
  esp_err_t begin();

 private:
};
