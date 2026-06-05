#include <Arduino.h>
#include "BluetoothA2DPSink.h"

constexpr int I2S_BCK_PIN = 25;
constexpr int I2S_WS_PIN = 26;
constexpr int I2S_DATA_PIN = 22;

BluetoothA2DPSink a2dpSink;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Bluetooth A2DP sink...");

  i2s_config_t i2sConfig = {
      .mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = 44100,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
      .dma_buf_count = 8,
      .dma_buf_len = 64,
      .use_apll = true,
      .tx_desc_auto_clear = true,
      .fixed_mclk = 0,
      .mclk_multiple = I2S_MCLK_MULTIPLE_DEFAULT,
      .bits_per_chan = I2S_BITS_PER_CHAN_DEFAULT,
  };

  i2s_pin_config_t pinConfig = {
      .mck_io_num = I2S_PIN_NO_CHANGE,
      .bck_io_num = I2S_BCK_PIN,
      .ws_io_num = I2S_WS_PIN,
      .data_out_num = I2S_DATA_PIN,
      .data_in_num = I2S_PIN_NO_CHANGE,
  };

  a2dpSink.set_i2s_config(i2sConfig);
  a2dpSink.set_pin_config(pinConfig);
  a2dpSink.start("Fabia BT Audio");
}

void loop() {
}
