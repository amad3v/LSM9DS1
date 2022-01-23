#include "mag.h"

using namespace mag;

Mag::Mag(
    I2C* i2c_ptr,
    mag::FSR m_range,
    mag::ODR m_rate,
    mag::OP_MODE m_mode,
    uint8_t addr) :
    Unit { i2c_ptr, addr },
    fsr { m_range },
    odr { m_rate },
    mode { m_mode } {}

bool Mag::valid_device_id() {
    uint8_t data {};
    return read(WHO_AM_I.address, &data) && (data == WHO_AM_I.value);
}

bool Mag::raw_m(int16_t data[]) {
    return raw_value(OUT_X_L, data);
}

bool Mag::read_m(float data[]) {
    int16_t buffer[3] {};

    if (raw_m(buffer)) {
        for (size_t idx = 0; idx < 3; idx++) {
            data[idx] = static_cast<float>(buffer[idx]) * mag::M_FSR_SO[fsr];
        }

        return true;
    }

    return false;
}

bool Mag::reset(uint8_t config) {
    return write(CTRL_REG2.address, config);
}

bool Mag::setup() {
    uint8_t ctrl_reg1 {};
    uint8_t ctrl_reg2 {};
    uint8_t ctrl_reg3 {};

    if (!(read(CTRL_REG1.address, &ctrl_reg1)
          && read(CTRL_REG2.address, &ctrl_reg2)
          && read(CTRL_REG3.address, &ctrl_reg3))) {
        return false;
    }

    if (!write(
            CTRL_REG1.address,
            shift_n_set(CTRL_REG1.odr, ctrl_reg1, odr)
                | CTRL_REG1.temp_comp.m_read_mask)) {
        return false;
    }

    if (!write(CTRL_REG2.address, shift_n_set(CTRL_REG2.fs, ctrl_reg2, fsr))) {
        return false;
    }

    if (!write(CTRL_REG3.address, shift_n_set(CTRL_REG3.md, ctrl_reg3, mode))) {
        return false;
    }

    return true;
}

bool Mag::available() {
    uint8_t buffer {};

    if (read(STATUS_REG.address, &buffer)) {
        return STATUS_REG.zyx_da.m_read_mask
            == (buffer & STATUS_REG.zyx_da.m_read_mask);
    }
    return false;
}