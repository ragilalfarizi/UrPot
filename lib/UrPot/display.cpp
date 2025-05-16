#include "display.h"

Display::Display(TwoWire &wire, uint8_t address)
    : _wire(wire), _address(address) {}

Display::~Display() {
  if (_oled) {
    delete _oled;
  }
}

esp_err_t Display::begin() {
  if (_oled) delete _oled;

  _oled = new Adafruit_SSD1306(DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_HEIGHT,
                               &_wire, -1);

  if (!_oled->begin(SSD1306_SWITCHCAPVCC, _address)) {
    return ESP_FAIL;
  }

  _oled->clearDisplay();
  _oled->display();

  return ESP_OK;
}

esp_err_t Display::print(const String &text, int16_t x, int16_t y, bool clear) {
  if (!_oled) return ESP_FAIL;

  if (clear) _oled->clearDisplay();
  _oled->setTextSize(1);
  _oled->setTextColor(SSD1306_WHITE);
  _oled->setCursor(x, y);
  _oled->print(text);
  _oled->display();

  return ESP_OK;
}
esp_err_t Display::clear() {
  if (!_oled) return ESP_FAIL;

  _oled->clearDisplay();
  _oled->display();

  return ESP_OK;
}
