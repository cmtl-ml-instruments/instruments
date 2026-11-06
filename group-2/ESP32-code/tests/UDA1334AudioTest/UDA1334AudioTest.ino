// Standalone tone test for the external UDA1334 DAC and headphone amplifier.
#include <Arduino.h>
#include <AMY-Arduino.h>
#include <driver/i2s_std.h>
#include <esp_err.h>

// Verified against the supplied ESP32-S3 board schematic:
// UART RXD -> GPIO44; UART TXD -> GPIO43. Reuse as I2S outputs.
// Leave the UART connector disconnected from any UART adapter/device.
#if !ARDUINO_USB_CDC_ON_BOOT
#error "Enable USB CDC On Boot: serial commands must use USB, not GPIO43/44."
#endif
constexpr int DAC_BCLK = 44;  // UART connector RXD
constexpr int DAC_WSEL = 43;  // UART connector TXD
constexpr int DAC_DIN = 45;   // Expansion connector IO45
constexpr int ONBOARD_PA_ENABLE = 1;
i2s_chan_handle_t dacTx = nullptr;

void sendMessage(const char *message) {
  char buffer[96];
  snprintf(buffer, sizeof(buffer), "%s", message);
  amy_add_message(buffer);
}

void setup() {
  // Keep the onboard speaker amplifier off while testing the external DAC.
  digitalWrite(ONBOARD_PA_ENABLE, HIGH);
  pinMode(ONBOARD_PA_ENABLE, OUTPUT);
  Serial.begin(115200);
  delay(500);

  amy_config_t config = amy_default_config();
  config.features.startup_bleep = 0;
  config.features.default_synths = 0;
  // Render one sine in the loop and stream it through our own Philips I2S
  // channel. The installed AMY driver uses MSB format instead of Philips I2S.
  config.platform.multithread = 0;
  config.platform.multicore = 0;
  config.audio = AMY_AUDIO_IS_NONE;
  config.features.audio_in = 0;
  config.i2s_mclk = -1;  // UDA1334 generates its system clock internally.
  config.i2s_bclk = DAC_BCLK;
  config.i2s_lrc = DAC_WSEL;
  config.i2s_dout = DAC_DIN;
  config.i2s_din = -1;
  amy_start(config);

  i2s_chan_config_t channel = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);
  ESP_ERROR_CHECK(i2s_new_channel(&channel, &dacTx, nullptr));
  i2s_std_config_t output = {};
  output.clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(AMY_SAMPLE_RATE);
  output.slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO);
  output.gpio_cfg.mclk = I2S_GPIO_UNUSED;
  output.gpio_cfg.bclk = static_cast<gpio_num_t>(DAC_BCLK);
  output.gpio_cfg.ws = static_cast<gpio_num_t>(DAC_WSEL);
  output.gpio_cfg.dout = static_cast<gpio_num_t>(DAC_DIN);
  output.gpio_cfg.din = I2S_GPIO_UNUSED;
  ESP_ERROR_CHECK(i2s_channel_init_std_mode(dacTx, &output));
  ESP_ERROR_CHECK(i2s_channel_enable(dacTx));

  // Oscillator 0: quiet 440 Hz sine, centered in stereo, initially silent.
  sendMessage("v0w0f440a0.05Q0.5l0");
  Serial.println("UDA1334 test ready; output is initially muted.");
  Serial.println("115200 baud: t=tone, m=mute, L=left, R=right, C=center.");
  Serial.println("Use a headphone amplifier with its volume turned down.");
}

void loop() {
  if (Serial.available()) {
    switch (Serial.read()) {
      case 't': sendMessage("v0l1"); Serial.println("Tone on"); break;
      case 'm': sendMessage("v0l0"); Serial.println("Muted"); break;
      case 'L': sendMessage("v0Q0"); Serial.println("Left channel"); break;
      case 'R': sendMessage("v0Q1"); Serial.println("Right channel"); break;
      case 'C': sendMessage("v0Q0.5"); Serial.println("Both channels"); break;
      default: break;
    }
  }
  int16_t *samples = amy_update();
  const uint8_t *bytes = reinterpret_cast<const uint8_t *>(samples);
  size_t remaining = AMY_BLOCK_SIZE * AMY_NCHANS * sizeof(int16_t);
  while (remaining > 0) {
    size_t written = 0;
    ESP_ERROR_CHECK(i2s_channel_write(dacTx, bytes, remaining, &written, portMAX_DELAY));
    bytes += written;
    remaining -= written;
  }
}
