#include "UrPot/UrPot.h"

UrPot *u = nullptr;

void setup() {
  u = new UrPot();
  if (!u) {
    ESP_LOGE(UrPot::TAG, "UrPot init is failed");
  }

  u->begin();
}

void loop() {}
