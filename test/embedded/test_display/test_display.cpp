#include <unity.h>

#include "UrPot/display.h"

TwoWire wireTest = TwoWire(1);
Display display(wireTest, I2C_ADDR_DISPLAY);

void setUp(void) {
  Serial.begin(115200);
  wireTest.begin(PIN_SDA_DISPLAY, PIN_SCl_DISPLAY);
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

  runUnityTests();
}
void loop() {}
