#ifndef _ES8311_H_
#define _ES8311_H_

#include <Arduino.h>
#include <Wire.h>

#define ES8311_I2C_ADDR 0x18
#define PA_ENABLE_PIN   1

class ES8311 {
public:
    ES8311();
    bool begin(TwoWire &wire = Wire, int sda = 38, int scl = 39, uint32_t frequency = 400000);
    bool init44KHz(bool bit32 = true);
    void setVolume(uint8_t volume); // 0 to 100
    void setMute(bool mute);
    void enableAmplifier(bool enable);
    uint8_t readReg(uint8_t reg);
    bool writeReg(uint8_t reg, uint8_t val);

private:
    TwoWire *_wire;
};

extern ES8311 es8311;

#endif // _ES8311_H_
