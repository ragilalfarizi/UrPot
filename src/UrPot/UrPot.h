#pragma once

#include <Arduino.h>
#include <esp_err.h>
#include <esp_log.h>

#include "BT_audio.h"
#include "display.h"
#include "filesystem.h"
#include "growlight_controller.h"
#include "rtc.h"

struct Data_t {
  DateTime now,
  DateTime schedule,
  GrowlightState light_state,
  BTState bt_state,
};

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
  GrowlightController *_light;
  BTAudio             *_ble;
  Display             *_disp;
  FileSystem          *_file;
  RTC                 *_rtc;
};
