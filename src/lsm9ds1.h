/**
 * @file lsm9ds1.h
 * @date 23.01.22
 * @author amad3v (amad3v@gmail.com)
 * @version 1.0.1
 *
 * @brief LSM9DS1 Class.
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

#ifndef __LIB__LSM9DS1_H__
#define __LIB__LSM9DS1_H__

#pragma GCC diagnostic ignored "-Wreorder"

#include <Arduino.h>
#include "i2c.h"
#include "xlg.h"
#include "mag.h"

/**
 * @class Sensor
 * @brief LSM9DS1 MARG Driver.
 */
class Sensor {
  public:
    /**
     * @brief Construct a new Sensor object.
     *
     * @param xl_range XL range/scale.
     * @param g_range G range/scale.
     * @param m_range M range/scale.
     * @param xlg_rate XL/G rate/frequency.
     * @param m_rate M rate/frequency.
     * @param m_mode M operating mode.
     * @see #XLG - #Mag
     */
    explicit Sensor(
        xlg::FSR_XL xl_range,
        xlg::FSR_G g_range,
        mag::FSR m_range,
        xlg::ODR xlg_rate,
        mag::ODR m_rate,
        mag::OP_MODE m_mode = mag::OP_MODE::CONTINUOUS);

    /**
     * @brief Initialise Sensor.
     *
     * @return true if succefully initialised,
     * @return false otherwise.
     */
    bool begin();

    /**
     * @brief Check if new values are available.
     *
     * @return true if new values,
     * @return false otherwise.
     */
    bool available();

    /**
     * @brief Read sensor values into 3 arrays.
     *
     * @param xl XL array.
     * @param g G array.
     * @param m M array.
     * @return true if succefully read,
     * @return false otherwise.
     */
    bool read(float xl[], float g[], float m[]);

    /**
     * @brief XLG unit.
     */
    XLG xlgSensor;

    /**
     * @brief M unit.
     */
    Mag mSensor;

  private:
    /**
     * @brief I2C communications manager.
     */
    I2C comms;
};

#endif /* __LIB__LSM9DS1_H__ */
