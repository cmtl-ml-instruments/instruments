#include "ES8311.h"

ES8311 es8311;

ES8311::ES8311() : _wire(&Wire) {}

bool ES8311::writeReg(uint8_t reg, uint8_t val) {
    if (!_wire) return false;
    _wire->beginTransmission(ES8311_I2C_ADDR);
    _wire->write(reg);
    _wire->write(val);
    return (_wire->endTransmission() == 0);
}

uint8_t ES8311::readReg(uint8_t reg) {
    if (!_wire) return 0;
    _wire->beginTransmission(ES8311_I2C_ADDR);
    _wire->write(reg);
    if (_wire->endTransmission(false) != 0) return 0;
    _wire->requestFrom((uint8_t)ES8311_I2C_ADDR, (uint8_t)1);
    if (_wire->available()) {
        return _wire->read();
    }
    return 0;
}

bool ES8311::begin(TwoWire &wire, int sda, int scl, uint32_t frequency) {
    _wire = &wire;
    _wire->begin(sda, scl, frequency);

    // Verify ES8311 presence by pinging I2C address
    _wire->beginTransmission(ES8311_I2C_ADDR);
    if (_wire->endTransmission() != 0) {
        Serial.printf("[ES8311] Error: Chip not found at I2C address 0x%02X\n", ES8311_I2C_ADDR);
        return false;
    }

    // Configure PA enable pin (Active LOW)
    pinMode(PA_ENABLE_PIN, OUTPUT);
    enableAmplifier(false); // keep muted until configured

    Serial.printf("[ES8311] Chip found at 0x%02X\n", ES8311_I2C_ADDR);
    return init44KHz(true);
}

bool ES8311::init44KHz(bool bit32) {
    // 1. Soft Reset
    writeReg(0x00, 0x1F);
    delay(25);
    writeReg(0x00, 0x00);
    delay(10);
    writeReg(0x00, 0x80); // Power on digital core

    // 2. Clock configuration for 44.1 kHz with MCLK = 256 * Fs = 11.2896 MHz
    // Reg 0x01: Master Clock source = MCLK pin (GPIO 17), enable internal clocks
    writeReg(0x01, 0x3F);

    // Reg 0x02: Pre-div = 1, Pre-multiplier = 1x
    writeReg(0x02, 0x00);

    // Reg 0x03: fs_mode = single speed (0), ADC OSR = 0x10
    writeReg(0x03, 0x10);

    // Reg 0x04: DAC OSR = 0x10
    writeReg(0x04, 0x10);

    // Reg 0x05: ADC div = 1, DAC div = 1
    writeReg(0x05, 0x00);

    // Reg 0x06: BCLK div = 4 (for 32-bit slot stereo, 64 BCLKs per frame)
    writeReg(0x06, 0x03);

    // Reg 0x07 & 0x08: LRCK dividers
    writeReg(0x07, 0x00);
    writeReg(0x08, 0xFF);

    // 3. Serial Data Port (SDP) configuration
    // Reg 0x09: DAC SDP format (I2S standard, bit32: 32-bit slot 0x10, 16-bit slot: 0x0C)
    uint8_t fmt_dac = bit32 ? (4 << 2) : (3 << 2);
    writeReg(0x09, fmt_dac);

    // Reg 0x0A: ADC SDP format
    writeReg(0x0A, fmt_dac);

    // 4. Power up analog, DAC and outputs
    writeReg(0x0D, 0x01); // Power up analog circuitry
    writeReg(0x0E, 0x02); // Enable analog PGA and ADC modulator
    writeReg(0x12, 0x00); // Power-up DAC
    writeReg(0x13, 0x10); // Enable output to headphone/speaker drive
    writeReg(0x1C, 0x6A); // Bypass ADC equalizer, cancel DC offset
    writeReg(0x37, 0x08); // Bypass DAC equalizer

    // 5. Unmute & set volume (default ~85%)
    setVolume(85);
    setMute(false);

    // 6. Enable onboard power amplifier (Active LOW)
    enableAmplifier(true);

    Serial.println("[ES8311] Configured for 44.1 kHz, PA amplifier enabled!");
    return true;
}

void ES8311::setVolume(uint8_t volume) {
    if (volume > 100) volume = 100;
    uint8_t regVal = (volume == 0) ? 0 : (uint8_t)(((uint32_t)volume * 256 / 100) - 1);
    writeReg(0x32, regVal);
}

void ES8311::setMute(bool mute) {
    uint8_t reg31 = readReg(0x31);
    if (mute) {
        reg31 |= 0x60; // Mute DAC
    } else {
        reg31 &= ~0x60; // Unmute DAC
    }
    writeReg(0x31, reg31);
}

void ES8311::enableAmplifier(bool enable) {
    // PA_ENABLE on GPIO 1 is ACTIVE LOW
    digitalWrite(PA_ENABLE_PIN, enable ? LOW : HIGH);
}
