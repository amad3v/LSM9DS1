/**
 * @file xlg.h
 * @date 23.01.22
 * @author amad3v (amad3v@gmail.com)
 * @version 1.0.1
 *
 * @brief Accelerometer/Gyroscope class.
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

#ifndef __LIB__LSM9DS1_DEF_XLG_H__
#define __LIB__LSM9DS1_DEF_XLG_H__

#include <Arduino.h>
#include "helpers.h"
#include "setting.h"
#include "unit.h"
#include "def.h"
#include "i2c.h"
#include "helpers.h"

using namespace xlg;

/**
 * @class XLG
 * @brief XL/G unit.
 */
class XLG : public Unit {
public:
  /**
   * @brief Construct a new XLG object.
   *
   * @param i2c_ptr Pointer to #I2C.
   * @param xl_range XL's range (full scale range).
   * @param g_range G's range (full scale range).
   * @param xlg_rate XL/G's rate (Output data rate).
   * @param addr XL/G's address.
   */
  XLG(I2C *i2c_ptr, FSR_XL xl_range, FSR_G g_range, ODR xlg_rate, uint8_t addr = ADDRESS);

  /**
   * @brief Check if M's ID is valid.
   *
   * @return true if valid,
   * @return false otherwise.
   */
  bool valid_device_id();

  /**
   * @brief Compute M's current values, in @f$\unitfrac{^{\circ}}{s}@f$.
   *
   * @param data Array to hold values.
   * @return true if read,
   * @return false otherwise.
   */
  bool read_g(float data[]);

  /**
   * @brief Compute M's current values, in @f$g@f$.<br>
   * @f$\unit[1]{g\approx9.81\unitfrac{m}{s^{2}}}@f$
   *
   * @param data Array to hold values.
   * @return true if read,
   * @return false otherwise.
   */
  bool read_xl(float data[]);

  /**
   * @brief Compute M's current values, in @f$^{\circ}@f$.
   *
   * @param data Array to hold values.
   * @return true if read,
   * @return false otherwise.
   */
  bool read_t(float &data);

  /**
   * @brief Reset M.
   *
   * @param config Configuration.
   * @return true if reset,
   * @return false otherwise.
   */
  bool reset(uint8_t config = DEFAULT_CONFIG);

  /**
   * @brief Setup M.
   *
   * @return true if set,
   * @return false otherwise.
   */
  bool setup();

  /**
   * @brief Check for XL/G new values.
   *
   * @return true if new values available.
   * @return false otherwise.
   */
  bool available();

  /**
   * @brief Check for XL new values.
   *
   * @return true if new values available.
   * @return false otherwise.
   */
  bool xl_available();

  /**
   * @brief Check for G new values.
   *
   * @return true if new values available.
   * @return false otherwise.
   */
  bool g_available();

  /**
   * @brief Check for T new values.
   *
   * @return true if new values available.
   * @return false otherwise.
   */
  bool t_available();

  /**
   * @brief Pitch [X-axis], Roll [Y-axis], Yaw [Z-axis] G sign.
   *
   * @param axes Axes to change sign.
   * @return true if written,
   * @return false otherwise.
   * @see Table 53
   */
  bool sign_axes_g(AXES_SIGN axes);

  /**
   * @brief Directional user orientation selection.
   *
   * @param orient Selected axes orientation.
   * @return true if written,
   * @return false otherwise.
   * @see Table 53
   */
  bool g_orientation(G_ORIENT orient);

  /**
   * @brief Set reference value for gyroscope’s digital high-pass filter.
   *
   * @param value Reference.
   * @return true if written,
   * @return false otherwise.
   */
  bool g_reference(uint8_t value);

  /**
   * @brief G bandwidth selection.
   *
   * @param value Selection.
   * @return true if written,
   * @return false otherwise.
   * @see Table 45/47
   */
  bool g_bandwidth(BW_G value);

  /**
   * @brief Set Anti-aliasing filter bandwidth selection.
   *
   * @param value Selection.
   * @return true if written,
   * @return false otherwise.
   * @see Table 67
   */
  bool xl_bandwidth(BW_XL value);

  /**
   * @brief Bandwidth selection mode.
   *
   * @param manual false: auto true: manual, use #xl_bandwidth.
   * @return true if written,
   * @return false otherwise.
   * @see Table 67
   */
  bool bandwidth_mode(bool manual);

  /**
   * @brief Enable/Disable low power mode.
   *
   * @param enable true: enable, false: disable
   * @return true if written,
   * @return false otherwise.
   * @warning If enabled, ODR will be set to @f$\unitfrac{119}{Hz}@f$ if
   * higher than @f$\unitfrac{119}{Hz}@f$.
   * If disabled, ODR will be set to @f$\unitfrac{238}{Hz}@f$ if lower than
   * @f$\unitfrac{238}{Hz}@f$.
   * @see Table 10
   */
  bool low_power(bool enable);

  /**
   * @brief Enable/Disable G axes output.
   *
   * @param axes Axes to set.
   * @param enable true: enable/false: disable.
   * @return true if written,
   * @return false otherwise.
   */
  bool axes_ouput_g(AXES_EN axes, bool enable);

  /**
   * @brief Enable/Disable XL axes output.
   *
   * @param axes Axes to set.
   * @param enable true: enable/false: disable.
   * @return true if written,
   * @return false otherwise.
   */
  bool axes_ouput_xl(AXES_EN axes, bool enable);

  /**
   * @brief High resolution mode.
   *
   * @param enable true: enable/false: disable.
   * @param cutoff Cutoff frequency, depends on ODR.
   * @return true if written,
   * @return false otherwise.
   */
  bool xl_high_res(bool enable, DCF cutoff = DCF::ODR_DIV_50);

private:
  /**
   * @brief G full scale range.
   */
  FSR_G fsr_g;

  /**
   * @brief XL full scale range.
   */
  FSR_XL fsr_xl;

  /**
   * @brief Output data rate.
   */
  ODR odr;

  /**
   * @brief Retrieve G raw data.
   *
   * @param data Array to hold values.
   * @return true if retrieved,
   * @return false otherwise
   */
  bool raw_g(int16_t data[]);

  /**
   * @brief Retrieve XL raw data.
   *
   * @param data Array to hold values.
   * @return true if retrieved,
   * @return false otherwise
   */
  bool raw_xl(int16_t data[]);

  /**
   * @brief Retrieve T raw data.
   *
   * @param data Array to hold values.
   * @return true if retrieved,
   * @return false otherwise
   */
  bool raw_t(int16_t data[]);

  /**
   * @brief Read a setting from STATUS_REG_1.
   *
   * @param mask Setting's mask.
   * @return true if read,
   * @return false otherwise.
   */
  bool status(uint8_t mask);

  /**
   * @brief Enable/Disable XL/G axes output.
   *
   * @tparam T @p reg type
   * @param reg XL or G register.
   * @param axes Axes to set.
   * @param enable true: enable/false: disable.
   * @return true if written,
   * @return false otherwise.
   */
  template <typename T> bool axes_ouput(T reg, AXES_EN axes, bool enable);
};

#endif /* __LIB__LSM9DS1_DEF_XLG_H__ */