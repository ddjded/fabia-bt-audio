#include <Arduino.h>
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

constexpr int I2S_BCK_PIN = 25;
constexpr int I2S_WS_PIN = 26;
constexpr int I2S_DATA_PIN = 22;

I2SStream i2s;
BluetoothA2DPSink a2dpSink(i2s);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Bluetooth A2DP sink...");

  auto cfg = i2s.defaultConfig();
  cfg.pin_bck = I2S_BCK_PIN;
  cfg.pin_ws = I2S_WS_PIN;
  cfg.pin_data = I2S_DATA_PIN;
  i2s.begin(cfg);

  a2dpSink.start("Fabia BT Audio");
}

void loop() {
}
