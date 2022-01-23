#include "unit.h"

Unit::Unit(I2C* i2c_ptr, uint8_t addr) : i2c { i2c_ptr }, address { addr } {}

bool Unit::read(uint8_t reg, uint8_t* data, size_t sz) {
    return sz == 1 ? i2c->readRegister(address, reg, data)
                   : i2c->readRegisters(address, reg, data, sz);
}

bool Unit::write(uint8_t reg, uint8_t value) {
    return i2c->writeRegister(address, reg, value);
}

bool Unit::raw_value(uint8_t reg, int16_t* data) {
    uint8_t buffer[6];

    if (read(reg, buffer, 6)) {
        for (size_t i {}; i < 3; i++) {
            size_t j { i * 2 };
            data[i] = shift_n_cast(buffer[j + 1], buffer[j]);
        }

        return true;
    }

    return false;
}