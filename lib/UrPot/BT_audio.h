#pragma once

#include <Arduino.h>
#include <esp_err.h>

#include "AudioTools.h"
#include "BluetoothA2DPSink.h"
// #include <freertos/FreeRTOS.h>

enum class BTState {
  DISCONNECTED,
  CONNECTED,
};

enum class AudioSource {
  BLUETOOTH,
  SD_CARD,
};

// class BTAudio {
//  public:
//   BTAudio(const char* name);
//   ~BTAudio();

//   esp_err_t   begin();
//   esp_err_t   playFromBLE();
//   esp_err_t   playFromFile(const char* path);
//   esp_err_t   stop();
//   BTState     getBTState();
//   AudioSource getCurrentSource();

//   static const char* TAG;

//  private:
//   BTState                  _btState;
//   AudioSource              _currentSource;
//   const char*              _deviceName;
//   BluetoothA2DPSink        _a2dp_sink;
//   AudioGeneratorMP3*       _mp3  = nullptr;
//   AudioFileSourceLittleFS* _file = nullptr;
//   AudioOutputI2S*          _out  = nullptr;

//   esp_err_t _setupI2S();
//   esp_err_t _setupBT();
//   esp_err_t _setupSDCard();
// };
