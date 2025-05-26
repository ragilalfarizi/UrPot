#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

// #include "BT_audio.h"
#include "BT_audio.h"
#include "button.h"
#include "display.h"
#include "growlight_controller.h"
#include "rtc.h"

// UrPot *u = nullptr;
// struct Data {};

/* TASK HANDLE DECLARATION */
TaskHandle_t display_hndlr   = nullptr;
TaskHandle_t button_hndlr    = nullptr;
TaskHandle_t BTAudio_hndlr   = nullptr;
TaskHandle_t growlight_hndlr = nullptr;
TaskHandle_t rtc_hndlr       = nullptr;

/* TASK FUNCTION DECLARATION */
void display_task(void *pvParameters);
void button_task(void *pvParameters);
void BTAudio_task(void *pvParameters);
void growlight_task(void *pvParameters);
void rtc_task(void *pvParameters);

RTC *rtc = nullptr;
// BTAudio             *bt_audio  = nullptr;
Display             *display       = nullptr;
GrowlightController *growlight     = nullptr;
Button              *mode_btn      = nullptr;
Button              *growlight_btn = nullptr;

MODE mode = MODE::MANUAL;

I2SStream         i2s;
AudioInfo         info(44100, 2, 32);  // Sample rate, channels, bits per sample
BluetoothA2DPSink a2dp_sink(i2s);
NumberFormatConverterStream convert(i2s);
SineWaveGenerator           generator(44100);

void setup() {
  // u = new UrPot();
  // if (!u) {
  //   ESP_LOGE(UrPot::TAG, "UrPot init is failed");
  // }
  //
  // u->begin();

  /* SERIAL INIT */
  Serial.begin(115200);

  /* BUTTON INIT */
  mode_btn = new Button(PIN_BTN_MODE);
  if (!mode_btn) {
    ESP_LOGE(Button::TAG, "Failed to create mode button");
  } else {
    mode_btn->begin();
  }

  // RTC = new ();

  auto cfg        = i2s.defaultConfig();
  cfg.pin_bck     = PIN_I2S_BCK;
  cfg.pin_ws      = PIN_I2S_LCK;
  cfg.pin_data    = PIN_I2S_DIN;
  cfg.sample_rate = 16;
  // cfg.copyFrom(info);  // Set the audio info to the I2S config

  i2s.begin(cfg);

  generator.begin(i2s);

  convert.begin(16, 32);

  a2dp_sink.start("MyMusic");

  /* TASK CONFIGURATION */
  // xTaskCreatePinnedToCore(display_task, "Display", 4096, nullptr, 1,
  //                         &display_hndlr, 0);
  // xTaskCreatePinnedToCore(button_task, "Button", 4096, nullptr, 1,
  //                         &button_hndlr, 0);
  // xTaskCreatePinnedToCore(BTAudio_task, "BTAudio", 8192, nullptr, 1,
  //                         &BTAudio_hndlr, 0);
  // xTaskCreatePinnedToCore(growlight_task, "Growlight", 4096, nullptr, 1,
  //                         &growlight_hndlr, 0);
  // xTaskCreatePinnedToCore(rtc_task, "RTC", 4096, nullptr, 1, &rtc_hndlr, 0);
}

void loop() { delay(1000); }

void display_task(void *pvParameters) {
  while (1) {
    /* code */
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void button_task(void *pvParameters) {
  while (1) {
    /* code */
    mode_btn->update();

    if (mode_btn->isPressed()) {
      ESP_LOGI(Button::TAG, "Mode button pressed");
      mode = (mode == MODE::MANUAL) ? MODE::AUTO : MODE::MANUAL;
      ESP_LOGI(Button::TAG, "Mode changed to: %s",
               (mode == MODE::MANUAL) ? "MANUAL" : "AUTO");
    } else {
      ESP_LOGI(Button::TAG, "Mode button not pressed");
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void BTAudio_task(void *pvParameters) {
  I2SStream         i2s;
  BluetoothA2DPSink a2dp_sink(i2s);

  auto cfg     = i2s.defaultConfig();
  cfg.pin_bck  = PIN_I2S_BCK;
  cfg.pin_ws   = PIN_I2S_LCK;
  cfg.pin_data = PIN_I2S_DIN;
  i2s.begin(cfg);

  a2dp_sink.start("MyMusic");

  while (1) {
    /* code */
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void growlight_task(void *pvParameters) {
  while (1) {
    /* code */
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void rtc_task(void *pvParameters) {
  while (1) {
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}
