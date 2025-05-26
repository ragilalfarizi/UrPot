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

struct UrPotState {
  MODE           mode_state;
  BTState        bt_state;
  GrowlightState growlight_state;
  RTCState       rtc_state;
};

UrPotState state;

struct UrPotData {
  DateTime current_time;
  DateTime schedule_start;
  DateTime schedule_end;
};

UrPotData data;

/* TASK HANDLE DECLARATION */
TaskHandle_t display_hndlr     = nullptr;
TaskHandle_t button_hndlr      = nullptr;
TaskHandle_t BTAudio_hndlr     = nullptr;
TaskHandle_t growlight_hndlr   = nullptr;
TaskHandle_t rtc_hndlr         = nullptr;
TaskHandle_t print_debug_hndlr = nullptr;

/* TASK FUNCTION DECLARATION */
void display_task(void *pvParameters);
void button_task(void *pvParameters);
void BTAudio_task(void *pvParameters);
void growlight_task(void *pvParameters);
void rtc_task(void *pvParameters);
void debug_task(void *pvParameters);

/* PERIPHERAL DECLARATION */
TwoWire i2c_bus = TwoWire(0);

/* OBJECT DECLARATION */
RTC                 *rtc           = nullptr;
Display             *display       = nullptr;
GrowlightController *growlight     = nullptr;
Button              *mode_btn      = nullptr;
Button              *growlight_btn = nullptr;
// BTAudio             *bt_audio  = nullptr;

// I2SStream         i2s;
// AudioInfo         info(44100, 2, 32);  // Sample rate, channels, bits per
// sample BluetoothA2DPSink a2dp_sink(i2s); NumberFormatConverterStream
// convert(i2s); SineWaveGenerator           generator(44100);

void setup() {
  /* SERIAL INIT */
  Serial.begin(115200);

  /* BUTTON INIT */
  mode_btn = new Button(PIN_BTN_MODE);
  if (!mode_btn) {
    ESP_LOGE(Button::TAG, "Failed to create mode button");
  } else {
    mode_btn->begin();
  }

  growlight_btn = new Button(PIN_BTN_GROWLIGHT);
  if (!growlight_btn) {
    ESP_LOGE(Button::TAG, "Failed to create growlight button");
  } else {
    growlight_btn->begin();
  }

  /* RTC INIT */
  i2c_bus.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  rtc = new RTC(i2c_bus);
  if (!rtc) {
    ESP_LOGE(RTC::TAG, "Failed to create RTC");
  } else {
    rtc->begin();
  }

  /* GROWLIGHT CONTROLLER INIT */
  growlight = new GrowlightController(PIN_RLY);
  if (!growlight) {
    ESP_LOGE(GrowlightController::TAG, "Failed to create Growlight Controller");
  } else {
    growlight->begin();
  }

  /* BT AUDIO INIT */
  // TODO: implement

  // auto cfg        = i2s.defaultConfig();
  // cfg.pin_bck     = PIN_I2S_BCK;
  // cfg.pin_ws      = PIN_I2S_LCK;
  // cfg.pin_data    = PIN_I2S_DIN;
  // cfg.sample_rate = 16;
  // cfg.copyFrom(info);  // Set the audio info to the I2S config

  // i2s.begin(cfg);

  // generator.begin(i2s);

  // convert.begin(16, 32);

  // a2dp_sink.start("MyMusic");

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
  xTaskCreatePinnedToCore(debug_task, "debug", 2048, nullptr, 1,
                          &print_debug_hndlr, 0);
}

void loop() { delay(1000); }

void display_task(void *pvParameters) {
  while (1) {
    if (state.mode_state == MODE::MANUAL) {
      display->print("Mode: MANUAL", 0, 0);
    } else {
      display->print("Mode: AUTO", 0, 0);
    }
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void button_task(void *pvParameters) {
  static uint32_t mode_btn_counter = 0;

  mode_btn->onClick([]() {
    mode_btn_counter++;
    ESP_LOGI(Button::TAG, "Mode button pressed");
  });

  while (1) {
    /* code */
    mode_btn->update();
    growlight_btn->update();

    if (mode_btn_counter % 2 == 0) {
      state.mode_state = MODE::MANUAL;
    } else {
      state.mode_state = MODE::AUTO;
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
  static uint32_t growlight_btn_counter = 0;

  growlight_btn->onClick([]() {
    growlight_btn_counter++;
    ESP_LOGI(Button::TAG, "Growlight button pressed");
  });

  while (1) {
    if (state.mode_state == MODE::MANUAL) {
      growlight_btn->update();

      if (growlight_btn_counter % 2 == 0) {
        if (state.growlight_state == GrowlightState::OFF) {
          growlight->on();
          state.growlight_state = GrowlightState::ON;
        } else {
          growlight->off();
          state.growlight_state = GrowlightState::OFF;
        }
      }
    } else {
      ESP_LOGD(GrowlightController::TAG, "Can't toggle growlight in AUTO mode");
    }
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void rtc_task(void *pvParameters) {
  rtc->getTimeDate(data.current_time);

  data.schedule_start =
      DateTime(data.current_time.year(), data.current_time.month(),
               data.current_time.day(), 8, 0,
               0);  // Start at 08:00:00

  data.schedule_end =
      DateTime((data.current_time.year(), data.current_time.month(),
                data.current_time.day(), 18, 0, 0));  // End at 18:00:00

  while (1) {
    // Update current time from RTC
    if (rtc->getTimeDate(data.current_time) == ESP_OK) {
      // Check if current time is within the schedule
      if (data.current_time >= data.schedule_start &&
          data.current_time <= data.schedule_end) {
        state.rtc_state = RTCState::INSIDE_SCHEDULE;
      } else {
        state.rtc_state = RTCState::OUTSIDE_SCHEDULE;
      }
    } else {
      // If RTC read fails, set OUTSIDE_SCHEDULE as a fallback
      state.rtc_state = RTCState::OUTSIDE_SCHEDULE;
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void debug_task(void *pvParameters) {
  while (1) {
    Serial.println("=========== STATE ==========");
    Serial.printf("Mode: %s\n",
                  (state.mode_state == MODE::MANUAL) ? "MANUAL" : "AUTO");
    Serial.printf("BT State: %s\n", (state.bt_state == BTState::DISCONNECTED)
                                        ? "DISCONNECTED"
                                        : "CONNECTED");
    Serial.printf(
        "Growlight State: %s\n",
        (state.growlight_state == GrowlightState::OFF) ? "OFF" : "ON");
    Serial.printf("RTC State: %s\n",
                  (state.rtc_state == RTCState::OUTSIDE_SCHEDULE)
                      ? "OUTSIDE_SCHEDULE"
                      : "INSIDE_SCHEDULE");
    Serial.println("=============================");

    Serial.println("=========== DATA ==========");
    Serial.printf("Current Time: %04d-%02d-%02d %02d:%02d:%02d\n",
                  data.current_time.year(), data.current_time.month(),
                  data.current_time.day(), data.current_time.hour(),
                  data.current_time.minute(), data.current_time.second());
    Serial.printf("Schedule Start: %04d-%02d-%02d %02d:%02d:%02d\n",
                  data.schedule_start.year(), data.schedule_start.month(),
                  data.schedule_start.day(), data.schedule_start.hour(),
                  data.schedule_start.minute(), data.schedule_start.second());
    Serial.printf("Schedule End: %04d-%02d-%02d %02d:%02d:%02d\n",
                  data.schedule_end.year(), data.schedule_end.month(),
                  data.schedule_end.day(), data.schedule_end.hour(),
                  data.schedule_end.minute(), data.schedule_end.second());
    Serial.println("=============================");

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
