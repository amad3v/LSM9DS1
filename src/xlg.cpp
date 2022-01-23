#include "xlg.h"

using namespace xlg;

XLG::XLG(
    I2C* i2c_ptr,
    xlg::FSR_XL xl_range,
    xlg::FSR_G g_range,
    xlg::ODR xlg_rate,
    uint8_t addr) :
    Unit { i2c_ptr, addr },
    fsr_g { g_range },
    fsr_xl { xl_range },
    odr { xlg_rate } {}

bool XLG::valid_device_id() {
    uint8_t data {};

    return read(WHO_AM_I.address, &data) && (data == WHO_AM_I.value);
}

bool XLG::raw_g(int16_t data[]) {
    return raw_value(OUT_X_L_G, data);
}

bool XLG::read_g(float data[]) {
    int16_t buffer[3] {};

    if (raw_g(buffer)) {
        set_list(buffer, data, xlg::G_FSR_SO[fsr_g]);
        return true;
    }
    return false;
}

bool XLG::raw_xl(int16_t data[]) {
    return raw_value(OUT_X_L_XL, data);
}

bool XLG::read_xl(float data[]) {
    int16_t buffer[3] {};

    if (raw_xl(buffer)) {
        set_list(buffer, data, xlg::XL_FSR_SO[fsr_xl]);
        return true;
    }
    return false;
}

bool XLG::raw_t(int16_t* data) {
    uint8_t buffer[2];

    if (read(OUT_TEMP_L, buffer, 2)) {
        data[0] = shift_n_cast(buffer[1], buffer[0]);
        return true;
    }

    return false;
}

bool XLG::read_t(float& data) {
    int16_t buffer {};

    if (raw_t(&buffer)) {
        data = static_cast<float>(buffer) / 16.0f + 25.0f;
        return true;
    }

    return false;
}

bool XLG::reset(uint8_t config) {
    return write(CTRL_REG8.address, config);
}

bool XLG::setup() {
    uint8_t ctrl_reg1_g {};
    uint8_t ctrl_reg6_xl {};

    delay(20);

    if (!(read(CTRL_REG1_G.address, &ctrl_reg1_g)
          && read(CTRL_REG6_XL.address, &ctrl_reg6_xl))) {
        return false;
    }

    if (!write(
            CTRL_REG1_G.address,
            shift_n_set(CTRL_REG1_G.fs_g, ctrl_reg1_g, fsr_g)
                | shift_n_set(CTRL_REG1_G.odr_g, ctrl_reg1_g, odr))) {
        return false;
    }

    if (!write(
            CTRL_REG6_XL.address,
            shift_n_set(CTRL_REG6_XL.fs_xl, ctrl_reg6_xl, fsr_xl)
                | shift_n_set(CTRL_REG6_XL.odr_xl, ctrl_reg6_xl, odr))) {
        return false;
    }

    return true;
}

bool XLG::available() {
    return g_available() && xl_available();
}

bool XLG::xl_available() {
    return status(STATUS_REG_1.xlda.m_read_mask);
}

bool XLG::g_available() {
    return status(STATUS_REG_1.gda.m_read_mask);
}

bool XLG::t_available() {
    return status(STATUS_REG_1.tda.m_read_mask);
}

bool XLG::status(uint8_t mask) {
    uint8_t buffer {};

    if (read(STATUS_REG_1.address, &buffer)) {
        return mask == (buffer & mask);
    }
    return false;
}