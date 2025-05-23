#include <unity.h>

#include "display.h"

TwoWire i2c_bus = TwoWire(0);
Display display(i2c_bus, I2C_ADDR_DISPLAY);

void setUp(void) {
  esp_err_t ret = display.begin();
  TEST_ASSERT_EQUAL(ESP_OK, ret);
}

void tearDown(void) {}

void test_display_begin() {
  esp_err_t result = display.begin();
  TEST_ASSERT_EQUAL(ESP_OK, result);
}

void test_display_print() {
  esp_err_t result = display.print("Hello, OLED!", 0, 0);
  TEST_ASSERT_EQUAL(ESP_OK, result);
}

void test_display_clear() {
  esp_err_t result = display.clear();
  TEST_ASSERT_EQUAL(ESP_OK, result);
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_display_begin);
  RUN_TEST(test_display_print);
  RUN_TEST(test_display_clear);
  return UNITY_END();
}

/**
 * For Arduino framework
 */
void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  Serial.begin(115200);
  i2c_bus.begin(PIN_SDA, PIN_SCL);

  runUnityTests();
}
void loop() {}
