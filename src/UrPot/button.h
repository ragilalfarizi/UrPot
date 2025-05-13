#pragma once

#include <Arduino.h>
#include <esp_err.h>

class Button{
 public:
  Button();
  ~Button();
  
  esp_err_t begin();

 private:
};
