/**
 * @file mag_ns.h
 * @date 23.01.22
 * @author amad3v (amad3v@gmail.com)
 * @version 1.0.1
 *
 * @brief Magnetometer namespace.
 *
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

#ifndef __LIB__LSM9DS1_NAMESPACE_MAG_NS_H__
#define __LIB__LSM9DS1_NAMESPACE_MAG_NS_H__

#include <Arduino.h>
#include "setting.h"

/*!
 *  @addtogroup mag
 *  @{
 */
//! M related types and constants
namespace mag {
/**
 * @brief M default address.
 * @see Table 20
 */
const uint8_t ADDRESS { 0x1e };

/**
 * @brief M default configuration.
 */
const uint8_t DEFAULT_CONFIG { 0x0c };

/**
 * @brief M sensitivity.
 * @see Table 3
 */
const float M_FSR_SO[4] {
    0.14e-3,
    0.29e-3,
    0.43e-3,
    0.58e-3,
};

/**
 * @enum FSR
 * @brief Magnetic measurement range.<br>
 * Unit: @f$Gauss@f$.
 * @see Table 112
 */
enum FSR {
    GAUSS_4,
    GAUSS_8,
    GAUSS_12,
    GAUSS_16,
};

/**
 * @enum ODR
 * @brief Magnetic output data rate.<br>
 * Unit: @f$Hz@f$.
 * @see Table 111
 */
enum ODR {
    R_0_625,
    R_1_25,
    R_2_5,
    R_5,
    R_10,
    R_20,
    R_40,
    R_80,
};

/**
 * @enum PERF_MODE
 * @brief Magnetometer operative mode (performance).<br>
 * Unit: N/A.
 * @see Table 110
 */
enum PERF_MODE {
    LOW_POWER,
    MEDIUM_PERF,
    HIGH_PERF,
    ULTRA_PERF,
};

/**
 * @enum OP_MODE
 * @brief Magnetometer operative/operating mode.<br>
 * Unit: N/A.
 * @see Table 110/117
 */
enum OP_MODE {
    CONTINUOUS,
    SINGLE,
    POWER_DOWN_1,
    POWER_DOWN_2,
};

/**
 * @brief X-axis LSB
 * @see section 8.11
 */
const uint8_t OUT_X_L { 0x28 };

/**
 * @brief Y-axis LSB
 * @see section 8.12
 */
const uint8_t OUT_Y_L { 0x2a };

/**
 * @brief Z-axis LSB
 * @see section 8.13
 */
const uint8_t OUT_Z_L { 0x2c };

/**
 * @brief WHO_AM_I register.
 * @see section 8.4
 */
struct {
    const uint8_t address { 0x0f };
    const uint8_t value { 0x3d };
} WHO_AM_I;

/**
 * @brief CTRL_REG1_M register
 * @see section 8.5
 */
struct {
    const uint8_t address { 0x20 };
    const Setting temp_comp { 0x80, 7 };
    const Setting om { 0x60, 5 };
    const Setting odr { 0x1c, 2 };
    const Setting fast_odr { 0x02, 1 };
    const Setting st { 0x01 };
} CTRL_REG1;

/**
 * @brief CTRL_REG2_M register
 * @see section 8.6
 */
struct {
    const uint8_t address { 0x21 };
    const Setting fs { 0x60, 5 };
    const Setting reboot { 0x08, 3 };
    const Setting soft_rst { 0x04, 2 };
} CTRL_REG2;

/**
 * @brief CTRL_REG3_M register
 * @see section 8.7
 */
struct {
    const uint8_t address { 0x22 };
    const Setting i2c_disable { 0x80, 7 };
    const Setting lp { 0x20, 5 };
    const Setting sim { 0x04, 2 };
    const Setting md { 0x03 };
} CTRL_REG3;

/**
 * @brief CTRL_REG4_M register
 * @see section 8.8
 */
struct {
    const uint8_t address { 0x23 };
    const Setting omz { 0x0c, 2 };
    const Setting ble { 0x02, 1 };
} CTRL_REG4;

/**
 * @brief STATUS_REG_M register
 * @see section 8.10
 */
struct {
    const uint8_t address { 0x27 };
    const Setting zyx_or { 0x80, 7 };
    const Setting z_or { 0x40, 6 };
    const Setting y_or { 0x20, 5 };
    const Setting x_or { 0x10, 4 };
    const Setting zyx_da { 0x08, 3 };
    const Setting z_da { 0x04, 2 };
    const Setting y_da { 0x02, 1 };
    const Setting x_da { 0x01 };
} STATUS_REG;

}  // namespace mag
/*! @} End of Doxygen Groups*/

#endif /* __LIB__LSM9DS1_NAMESPACE_MAG_NS_H__ */