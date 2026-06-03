#include <Arduino.h>
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

BluetoothA2DPSink a2dpSink;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Bluetooth A2DP sink...");

  a2dpSink.start("Fabia BT Audio");
}

void loop() {
}
