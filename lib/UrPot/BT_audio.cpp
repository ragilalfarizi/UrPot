#include "BT_audio.h"

const char* BTAudio::TAG = "BLE";

BTAudio::BTAudio(const char* name)
    : _btState(BTState::DISCONNECTED),
      _currentSource(AudioSource::SD_CARD),
      _deviceName(name) {}

BTAudio::~BTAudio() {}

esp_err_t BTAudio::begin() {
  // TODO: filesystem init
  // TODO: ble init
  return ESP_FAIL;
}

esp_err_t BTAudio::begin() {
  _setupI2S();
  _setupBT();
  _setupSDCard();
  return ESP_OK;
}

void BTAudio::_setupI2S() {
  _out = new AudioOutputI2S();
  _out->SetPinout(26, 25, 22);  // BCLK, LRCLK, DATA (adjust if needed)
  _out->SetGain(0.8);
}

void BTAudio::_setupBT() {
  _a2dp_sink.set_stream_writer(_out);
  _a2dp_sink.set_on_connection_state_changed([this](bool connected) {
    _btState = connected ? BTState::CONNECTED : BTState::DISCONNECTED;
    if (connected) _currentSource = AudioSource::BLUETOOTH;
  });
  _a2dp_sink.start(_deviceName);
}

// void BTAudio::_setupSDCard() {
//   if (!LittleFS.begin()) {
//     Serial.println("LittleFS mount failed");
//   }
// }

esp_err_t BTAudio::playFromBLE() {
  _currentSource = AudioSource::BLUETOOTH;
  return ESP_OK;  // No explicit play command needed for A2DP Sink
}

esp_err_t BTAudio::playFromFile(const char* path) {
  if (_currentSource == AudioSource::BLUETOOTH) a2dp_sink.end();

  _file = new AudioFileSourceLittleFS(path);
  _mp3  = new AudioGeneratorMP3();
  _mp3->begin(_file, _out);
  _currentSource = AudioSource::SD_CARD;

  return ESP_OK;
}

esp_err_t BTAudio::stop() {
  if (_currentSource == AudioSource::SD_CARD && _mp3) {
    _mp3->stop();
    delete _mp3;
    _mp3 = nullptr;

    delete _file;
    _file = nullptr;
  } else if (_currentSource == AudioSource::BLUETOOTH) {
    _a2dp_sink.end();
  }
  _currentSource = AudioSource::BLUETOOTH;
  return ESP_OK;
}

BTState BTAudio::getBTState() { return _btState; }

AudioSource BTAudio::getCurrentSource() { return _currentSource; }
