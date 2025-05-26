#pragma once

// Pin out mapping
#define PIN_I2C_SDA       23
#define PIN_I2C_SCL       22
#define PIN_RLY           5
#define PIN_BTN_MODE      34
#define PIN_BTN_GROWLIGHT 19
#define PIN_I2S_LCK       4
#define PIN_I2S_DIN       16
#define PIN_I2S_BCK       17
#define PIN_SD_CS         26
#define PIN_SD_MOSI       25
#define PIN_SD_MISO       27
#define PIN_SD_SCK        32

// Configurations
#define DISPLAY_SCREEN_WIDTH  128
#define DISPLAY_SCREEN_HEIGHT 64
#define DISPLAY_ADDRESS       0x3C

enum class MODE {
  MANUAL,
  AUTO,
};
