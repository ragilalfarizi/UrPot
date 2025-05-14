#include <unity.h>

#include "UrPot/growlight_controller.h"

#define TEST_GROWLIGHT_PIN 5

GrowlightController growlight(TEST_GROWLIGHT_PIN);

void setUp(void) { Serial.begin(115200); }

void tearDown(void) {}

void test_growlight_on_off_toggle() {
  growlight.begin();

  growlight.on();
  TEST_ASSERT_EQUAL(GrowlightState::ON, growlight.getState());

  growlight.off();
  TEST_ASSERT_EQUAL(GrowlightState::OFF, growlight.getState());

  growlight.toggle();
  TEST_ASSERT_EQUAL(GrowlightState::ON, growlight.getState());

  growlight.toggle();
  TEST_ASSERT_EQUAL(GrowlightState::OFF, growlight.getState());
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_growlight_on_off_toggle);
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
