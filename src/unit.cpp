/**
 * @file unit.cpp
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