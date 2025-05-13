#pragma once

#include <Arduino.h>
#include <esp_err.h>

class FileSystem{
 public:
  FileSystem();
  ~FileSystem();

  esp_err_t begin();

 private:
};
