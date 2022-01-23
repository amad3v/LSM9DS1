/**
 * @file xlg.cpp
 * @date 23.01.22
 * @author amad3v (amad3v@gmail.com)
 * @version 1.0.1
 * @copyright Copyright (c) 2022
 *
 * This file is part of LSM9DS1.
 *
 * LSM9DS1 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License.
 *
 * LSM9DS1 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LSM9DS1.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "xlg.h"

using namespace xlg;

XLG::XLG(
    I2C* i2c_ptr,
    FSR_XL xl_range,
    FSR_G g_range,
    ODR xlg_rate,
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
        set_list(buffer, data, G_FSR_SO[fsr_g]);
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
        set_list(buffer, data, XL_FSR_SO[fsr_xl]);
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

bool XLG::sign_axes_g(AXES_SIGN axes) {
    uint8_t current {};

    if (!read(ORIENT_CFG_G.address, &current)) {
        return false;
    }

    return write(
        ORIENT_CFG_G.address,
        shift_n_set(ORIENT_CFG_G.sign_xyz_g, current, axes));
}

bool XLG::g_orientation(G_ORIENT orient) {
    uint8_t current {};

    if (!read(ORIENT_CFG_G.address, &current)) {
        return false;
    }

    return write(
        ORIENT_CFG_G.address,
        shift_n_set(ORIENT_CFG_G.orient, current, orient));
}

bool XLG::g_reference(uint8_t value) {
    return write(REFERENCE_G, value);
}

bool XLG::g_bandwidth(BW_G value) {
    uint8_t current {};

    if (!read(CTRL_REG1_G.address, &current)) {
        return false;
    }

    return write(
        CTRL_REG1_G.address,
        shift_n_set(CTRL_REG1_G.bw_g, current, value));
}

bool XLG::xl_bandwidth(BW_XL value) {
    uint8_t current {};

    if (!read(CTRL_REG6_XL.address, &current)) {
        return false;
    }

    return write(
        CTRL_REG6_XL.address,
        shift_n_set(CTRL_REG6_XL.bw_xl, current, value));
}

bool XLG::bandwidth_mode(bool manual) {
    uint8_t current {};

    if (!read(CTRL_REG6_XL.address, &current)) {
        return false;
    }

    return write(
        CTRL_REG6_XL.address,
        shift_n_set(CTRL_REG6_XL.bw_scal_odr, current, U(manual)));
}

bool XLG::low_power(bool enable) {
    uint8_t current {}, current_odr {};

    if (!(read(CTRL_REG1_G.address, &current_odr)
          && read(CTRL_REG3_G.address, &current))) {
        return false;
    }

    uint8_t odr { mask_n_shift(CTRL_REG1_G.odr_g, current_odr) };
    uint8_t new_odr {};

    if (enable && (odr > ODR::R_119)) {
        new_odr = ODR::R_119;
    } else if (!enable && (odr < ODR::R_238)) {
        new_odr = ODR::R_238;
    }

    if (odr != new_odr) {
        if (!(write(
                  CTRL_REG1_G.address,
                  shift_n_set(CTRL_REG1_G.odr_g, current_odr, new_odr))
              && write(
                  CTRL_REG6_XL.address,
                  shift_n_set(CTRL_REG6_XL.odr_xl, current_odr, new_odr)))) {
            return false;
        }
    }

    return write(
        CTRL_REG3_G.address,
        shift_n_set(CTRL_REG3_G.lp_mode, current, U(enable)));
}

bool XLG::axes_ouput_g(AXES_EN axes, bool enable) {
    return axes_ouput(CTRL_REG4, axes, enable);
}

bool XLG::axes_ouput_xl(AXES_EN axes, bool enable) {
    return axes_ouput(CTRL_REG5_XL, axes, enable);
}

bool XLG::xl_high_res(bool enable, DCF cutoff) {
    uint8_t current {};

    if (!read(CTRL_REG7_XL.address, &current)) {
        return false;
    }

    current = shift_n_set(CTRL_REG7_XL.hr, current, U(enable));

    return write(
        CTRL_REG7_XL.address,
        shift_n_set(CTRL_REG7_XL.dcf, current, cutoff));
}

template<typename T>
bool XLG::axes_ouput(T reg, AXES_EN axes, bool enable) {
    uint8_t current {};

    if (!read(reg.address, &current)) {
        return false;
    }

    return write(
        reg.address,
        shift_n_set(reg.xyz_enable, current, enable ? axes : 0x07 ^ axes));
}