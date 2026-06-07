#include <Arduino.h>
#include <driver/i2s.h>
#include <math.h>

constexpr i2s_port_t I2S_PORT = I2S_NUM_0;

constexpr int I2S_BCK_PIN = 26;
constexpr int I2S_WS_PIN = 25;
constexpr int I2S_DATA_PIN = 22;

constexpr uint32_t SAMPLE_RATE = 44100;
constexpr float TONE_FREQUENCY = 1000.0f;
constexpr int16_t TONE_AMPLITUDE = 3000;
constexpr size_t FRAME_COUNT = 441;

int16_t sampleBuffer[FRAME_COUNT * 2];

void setup() {
  Serial.begin(115200);

  i2s_config_t i2sConfig = {
      .mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = SAMPLE_RATE,
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

  i2s_driver_install(I2S_PORT, &i2sConfig, 0, nullptr);
  i2s_set_pin(I2S_PORT, &pinConfig);
  i2s_zero_dma_buffer(I2S_PORT);

  constexpr float FULL_CYCLE_RADIANS = 2.0f * PI;
  constexpr float PHASE_STEP =
      FULL_CYCLE_RADIANS * TONE_FREQUENCY / SAMPLE_RATE;

  for (size_t frame = 0; frame < FRAME_COUNT; ++frame) {
    const int16_t sample = static_cast<int16_t>(
        sinf(frame * PHASE_STEP) * TONE_AMPLITUDE);

    sampleBuffer[frame * 2] = sample;
    sampleBuffer[frame * 2 + 1] = sample;
  }

  Serial.println("I2S tone test started");
}

void loop() {
  size_t bytesWritten = 0;
  i2s_write(I2S_PORT, sampleBuffer, sizeof(sampleBuffer), &bytesWritten,
            portMAX_DELAY);
}
