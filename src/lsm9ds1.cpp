/**
 * @file lsm9ds1.cpp
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

#include "lsm9ds1.h"

Sensor::Sensor(
    xlg::FSR_XL xl_range,
    xlg::FSR_G g_range,
    mag::FSR m_range,
    xlg::ODR xlg_rate,
    mag::ODR m_rate,
    mag::OP_MODE m_mode) :
    comms { I2C {} },
    xlgSensor { &comms, xl_range, g_range, xlg_rate },
    mSensor { &comms, m_range, m_rate, m_mode } {}

bool Sensor::begin() {
    comms.begin();
    if (!(xlgSensor.valid_device_id() && xlgSensor.reset() && xlgSensor.setup()
          && mSensor.valid_device_id() && mSensor.reset() && mSensor.setup())) {
        comms.end();
        return false;
    }

    return true;
}

bool Sensor::available() {
    return xlgSensor.available() && mSensor.available();
}

bool Sensor::read(float xl[], float g[], float m[]) {
    return (xlgSensor.read_xl(xl) && xlgSensor.read_g(g) && mSensor.read_m(m));
}