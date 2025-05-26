#include <unity.h>

#include "growlight_controller.h"

GrowlightController growlight(PIN_RLY);

void setUp(void) { growlight.begin(); }

void tearDown(void) {}

void test_growlight_on_off_toggle() {
  growlight.on();
  TEST_ASSERT_EQUAL(GrowlightState::ON, growlight.getState());
  delay(1000);  // Wait for 1 second

  growlight.off();
  TEST_ASSERT_EQUAL(GrowlightState::OFF, growlight.getState());
  delay(1000);  // Wait for 1 second

  growlight.toggle();
  TEST_ASSERT_EQUAL(GrowlightState::ON, growlight.getState());
  delay(1000);  // Wait for 1 second

  growlight.toggle();
  TEST_ASSERT_EQUAL(GrowlightState::OFF, growlight.getState());
  delay(1000);  // Wait for 1 second
}

void test_return_state() {
  growlight.on();
  TEST_ASSERT_EQUAL(GrowlightState::ON, growlight.getState());
  delay(1000);  // Wait for 1 second

  growlight.off();
  TEST_ASSERT_EQUAL(GrowlightState::OFF, growlight.getState());
  delay(1000);  // Wait for 1 second
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_growlight_on_off_toggle);
  RUN_TEST(test_return_state);
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

  runUnityTests();
}
void loop() {}
