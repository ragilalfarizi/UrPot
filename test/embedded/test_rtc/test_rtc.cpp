#include <rtc.h>
#include <unity.h>

#include "defs.h"

RTC    *rtc     = nullptr;
TwoWire i2c_bus = TwoWire(0);

void setUp(void) {
  esp_err_t ret = rtc->begin();
  TEST_ASSERT_EQUAL(ESP_OK, ret);
}

void tearDown(void) {}

void test_init(void) {
  esp_err_t ret;
  ret = rtc->begin();
  TEST_ASSERT_EQUAL(ret, ESP_OK);
}

void test_set_and_get_time() {
  DateTime setTime(2025, 5, 13, 15, 30, 0);
  DateTime now;

  esp_err_t set_result = rtc->setTimeDate(setTime);
  TEST_ASSERT_EQUAL_HEX8(ESP_OK, set_result);

  esp_err_t get_result = rtc->getTimeDate(now);
  TEST_ASSERT_EQUAL_HEX8(ESP_OK, get_result);

  // Allow small difference due to potential clock tick delay
  TEST_ASSERT_EQUAL(setTime.year(), now.year());
  TEST_ASSERT_EQUAL(setTime.month(), now.month());
  TEST_ASSERT_EQUAL(setTime.day(), now.day());
  TEST_ASSERT_EQUAL(setTime.hour(), now.hour());
  TEST_ASSERT_EQUAL(setTime.minute(), now.minute());

  // Second may differ due to delay between set/get
  int secDiff = abs(setTime.second() - now.second());
  TEST_ASSERT_LESS_THAN_INT(2, secDiff);  // allow up to 1 second drift
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_init);
  RUN_TEST(test_set_and_get_time);
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
  Wire.begin(PIN_SDA, PIN_SCL);

  rtc = new RTC(Wire);

  runUnityTests();
}
void loop() {}
