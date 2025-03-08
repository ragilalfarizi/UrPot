#pragma once

#include <Arduino.h>
#include <esp_err.h>

#include "BTAudio.h"
#include "environment_sensor.h"
#include "relay_controller.h"
#include "soil_sensor.h"

class Bomz {
 public:
  /* CONSTRUCTOR AND DESTRUCTOR */
  Bomz();
  ~Bomz();

  esp_err_t begin();

  /* TASK DECLARATION AND HANDLER */

 private:
  RelayController   relay;
  EnvironmentSensor env;
  BTAudio           ble;
  SoilSensor        soil;
  // LightSensor light;
};
