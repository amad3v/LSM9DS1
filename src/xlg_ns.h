/**
 * @file xlg_ns.h
 * @date 23.01.22
 * @author amad3v (amad3v@gmail.com)
 * @version 1.0.1
 *
 * @brief Accelerometer/Gyroscope namespace.
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

#ifndef __LIB__LSM9DS1_NAMESPACE_XLG_NS_H__
#define __LIB__LSM9DS1_NAMESPACE_XLG_NS_H__

#include <Arduino.h>
#include "setting.h"

/*!
 *  @addtogroup xlg
 *  @{
 */
//! XL/G related types and constants
namespace xlg {
/**
 * @brief Convert bool to unsigned int.
 */
inline uint8_t U(bool b) { return b ? 1u : 0u; }

/**
 * @brief XL/G default address.
 * @see Table 19
 */
const uint8_t ADDRESS{0x6b};

/**
 * @brief XL/G default config.
 */
const uint8_t DEFAULT_CONFIG{0x05};

/**
 * @brief XL sensitivity.
 * @see Table 3
 */
const float XL_FSR_SO[4]{
    0.061e-3,
    0.732e-3,
    0.122e-3,
    0.244e-3,
};

/**
 * @brief G sensitivity.
 * @see Table 3
 */
const float G_FSR_SO[3]{
    8.75e-3,
    17.5e-3,
    70.0e-3,
};

/**
 * @enum FSR_XL
 * @brief Linear acceleration measurement range.<br>
 * Unit: @f$g@f$ [@f$\unit[1]{g\approx 9.81\unitfrac{m}{s^{2}}}@f$].
 * @see Table 67
 */
enum FSR_XL {
  G_2,
  G_16,
  G_4,
  G_8,
};

/**
 * @enum FSR_G
 * @brief G measurement range.<br>
 * Unit: @f$dps@f$ [@f$\unitfrac{^{\circ}}{s}@f$].
 * @see Table 45
 */
enum FSR_G {
  DPS_245,
  DPS_500,
  DPS_2000 = 0x03,
};

/**
 * @enum ODR
 * @brief XL/G output data rate.<br>
 * Unit: @f$Hz@f$.
 * @see Table 45/67
 */
enum ODR {
  R_OFF,
  R_14_9,
  R_59_5,
  R_119,
  R_238,
  R_476,
  R_952,
};

/**
 * @enum BW_G
 * @brief G bandwidth selection.
 * @see Table 45/47.
 */
enum BW_G {
  BW_0,
  BW_1,
  BW_2,
  BW_3,
};

/**
 * @brief XL Bandwidth selection.<br>
 * Default value: 0x00.<br>
 *  - 0: bandwidth determined by ODR selection.
 *  - 1: bandwidth selected according to BW_XL [2:1] selection.
 * @see Table 67.
 */
enum BW_SCALE_XL {
  AUTO,
  MANUAL,
};

/**
 * @brief Anti-aliasing filter bandwidth selection.<br>
 * Default value: 0x00 [408 Hz]
 * @see Table 67
 */
enum BW_XL {
  BW_408,
  BW_211,
  BW_105,
  BW_50,
};

/**
 * @enum AXES_SIGN
 * @brief G axes sign.
 * @see Table 54
 */
enum AXES_SIGN {
  AS_Z = 1,
  AS_Y,
  AS_YZ,
  AS_X,
  AS_XZ,
  AS_XY,
  AS_XYZ,
};

/**
 * @enum G_ORIENT
 * @brief G axes orientation.
 * @see Table 54
 */
enum G_ORIENT {
  XYZ,
  XZY,
  YXZ,
  YZX,
  ZXY,
  ZYX,
};

/**
 * @enum AXES_EN
 *  @brief Enabled axes
 * @see Table 63/65
 */
enum AXES_EN {
  EN_X = 1,
  EN_Y,
  EN_XY,
  EN_Z,
  EN_XZ,
  EN_YZ,
  EN_XYZ,
};

/**
 * @enum DCF
 * @brief XL digital filter.
 * @see Table 71
 */
enum DCF {
  ODR_DIV_50,
  ODR_DIV_100,
  ODR_DIV_9,
  ODR_DIV_400,
};

/**
 * @brief G sensor reference value register for digital high-pass filter.
 * @see section 7.8
 */
const uint8_t REFERENCE_G{0x0b};

/**
 * @brief T data output register (LSB).
 * @see section 7.17
 */
const uint8_t OUT_TEMP_L{0x15};

/**
 * @brief G X-axis LSB
 * @see section 7.19
 */
const uint8_t OUT_X_L_G{0x18};

/**
 * @brief G Y-axis LSB
 * @see section 7.20
 */
const uint8_t OUT_Y_L_G{0x1a};

/**
 * @brief G Z-axis LSB
 * @see section 7.21
 */
const uint8_t OUT_Z_L_G{0x1c};

/**
 * @brief XL X-axis LSB
 * @see section 7.31
 */
const uint8_t OUT_X_L_XL{0x28};

/**
 * @brief XL Y-axis LSB
 * @see section 7.32
 */
const uint8_t OUT_Y_L_XL{0x2a};

/**
 * @brief XL Z-axis LSB
 * @see section 7.33
 */
const uint8_t OUT_Z_L_XL{0x2c};

/**
 * @brief Who_AM_I register.
 * @see section 7.11
 */
struct {
  const uint8_t address{0x0f};
  const uint8_t value{0x68};
} WHO_AM_I;

/**
 * @brief CTRL_REG1_G register.
 * @see section 7.12
 */
struct {
  const uint8_t address{0x10};
  const Setting odr_g{0xe0, 5};
  const Setting fs_g{0x18, 3};
  const Setting bw_g{0x03};
} CTRL_REG1_G;

/**
 *  @brief CTRL_REG6_XL register.
 * @see section 7.24
 */
struct {
  const uint8_t address{0x20};
  const Setting odr_xl{0xe0, 5};
  const Setting fs_xl{0x18, 3};
  const Setting bw_scal_odr{0x04, 2};
  const Setting bw_xl{0x03};
} CTRL_REG6_XL;

/**
 * @brief CTRL_REG3_G register.
 * @see section 7.14
 */
struct {
  const uint8_t address{0x12};
  const Setting lp_mode{0x80, 7};
  const Setting hp_en{0x40, 6};
  const Setting hpcf_g{0x0f};
} CTRL_REG3_G;

/**
 * @brief CTRL_REG4 register.
 * @see section 7.22
 */
struct {
  const uint8_t address{0x1e};
  const Setting xyz_enable{0x38, 3};
  const Setting lir_xl1{0x02, 1};
  const Setting xl1_4d{0x01};
} CTRL_REG4;

/**
 * @brief CTRL_REG5_XL register.
 * @see section 7.23
 */
struct {
  const uint8_t address{0x1f};
  const Setting dec{0xc0, 6};
  const Setting xyz_enable{0x38, 3};
} CTRL_REG5_XL;

/**
 * @brief ORIENT_CFG_G register.<br>
 * @image html axes_orient.png "Axes orientation"
 * @see section 7.15
 */
struct {
  const uint8_t address{0x13};
  const Setting sign_xyz_g{0x38, 3};
  const Setting orient{0x07};
} ORIENT_CFG_G;

/**
 * @brief STATUS_REG_1 register.
 * @see section 7.18
 */
struct {
  const uint8_t address{0x17};
  const Setting ig_xl{0x40, 6};
  const Setting ig_g{0x20, 5};
  const Setting inact{0x10, 4};
  const Setting boot_status{0x08, 3};
  const Setting tda{0x04, 2};
  const Setting gda{0x02, 1};
  const Setting xlda{0x01};
} STATUS_REG_1;

/**
 * @brief CTRL_REG7_XL register.
 * @see section 7.25
 */
struct {
  const uint8_t address{0x21};
  const Setting hr{0x80, 7};
  const Setting dcf{0x60, 5};
  const Setting fds{0x04, 2};
  const Setting hpis{0x01};
} CTRL_REG7_XL;

/**
 * @brief CTRL_REG8 register.
 * @see section 7.26
 */
struct {
  const uint8_t address{0x22};
  const Setting boot{0x80, 7};
  const Setting bdu{0x40, 6};
  const Setting h_lactive{0x20, 5};
  const Setting pp_od{0x10, 4};
  const Setting sim{0x08, 3};
  const Setting if_add_inc{0x04, 2};
  const Setting ble{0x02, 1};
  const Setting sw_reset{0x01};
} CTRL_REG8;

/**
 * @brief CTRL_REG10 register.
 * @see section 7.28
 */
struct {
  const uint8_t address{0x24};
  const Setting st_g{0x04, 2};
  const Setting st_xl{0x01};
} CTRL_REG10;

} // namespace xlg
/*! @} End of Doxygen Groups*/

#endif /* __LIB__LSM9DS1_NAMESPACE_XLG_NS_H__ */