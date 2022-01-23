#include "i2c.h"

I2C::I2C() : i2c { &Wire1 } {}

I2C::~I2C() {}

void I2C::begin() {
    i2c->begin();
}

bool I2C::readRegister(uint8_t unitAddress, uint8_t reg, uint8_t* data) {
    uint8_t buffer[1] {};

    if (readRegisters(unitAddress, reg, buffer, 1)) {
        *data = buffer[0];
        return true;
    }

    return false;
}

bool I2C::readRegisters(
    uint8_t unitAddress,
    uint8_t reg,
    uint8_t* data,
    size_t sz) {
    bool single { sz == 1 };

    i2c->beginTransmission(unitAddress);
    i2c->write(single ? reg : 0x80 | reg);
    if (i2c->endTransmission(single) != 0) {
        return false;
    }

    if (i2c->requestFrom(unitAddress, sz) != sz) {
        return false;
    }

    for (size_t i = 0; i < sz; i++) {
        *data++ = i2c->read();
    }

    return true;
}

bool I2C::writeRegister(uint8_t unitAddress, uint8_t reg, uint8_t value) {
    i2c->beginTransmission(unitAddress);
    i2c->write(reg);
    i2c->write(value);
    return i2c->endTransmission() == 0;
}

void I2C::end() {
    i2c->end();
}