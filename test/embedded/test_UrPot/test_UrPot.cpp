#include <unity.h>

#include "UrPot/UrPot.h"

UrPot *up = nullptr;

void setUp(void) {
 Serial.begin(115200);

  up = new UrPot();
}

void tearDown(void) {
  delete up;
}

void test_init(void) {
  esp_err_t ret;
  ret = up->begin();
 TEST_ASSERT_EQUAL(ret, ESP_OK);
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_init);
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
