#pragma once

#include <Arduino.h>
#include <esp_err.h>
#include <esp_log.h>
#include <rtc.h>

// #include "BT_audio.h"
#include "display.h"
#include "growlight_controller.h"

class UrPot {
 public:
  /* CONSTRUCTOR AND DESTRUCTOR */
  UrPot();
  ~UrPot();

  esp_err_t begin();

  /* MEMBER DECLARATION */
  static const char *TAG;

  /* TASK DECLARATION AND HANDLER */

 private:
  GrowlightController *_light = nullptr;
  // BTAudio             *_ble   = nullptr;
  Display *_disp = nullptr;
  RTC     *_rtc  = nullptr;
};
