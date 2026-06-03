#include <Arduino.h>

constexpr uint8_t LED_PIN = 2;
constexpr unsigned long BLINK_INTERVAL_MS = 500;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting blink...");
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(BLINK_INTERVAL_MS);
  digitalWrite(LED_PIN, LOW);
  delay(BLINK_INTERVAL_MS);
}
