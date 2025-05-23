#include <unity.h>

#include "UrPot/button.h"

#define TEST_BUTTON_PIN 4

Button button(TEST_BUTTON_PIN);
bool   clicked = false;

void setUp(void) { Serial.begin(115200); }

void tearDown(void) {}

void clickHandler() { clicked = true; }

void test_button_click_event() {
  button.begin();
  button.onClick(clickHandler);

  // Simulate click (on real hardware you'd press button)
  clicked = false;
  for (int i = 0; i < 20; ++i) {
    button.update();
    delay(10);
  }

  TEST_ASSERT_TRUE_MESSAGE(clicked, "Button should trigger onClick()");
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_button_click_event);
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
