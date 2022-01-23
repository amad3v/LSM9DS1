/**
 * @file helpers.cpp
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

#include "helpers.h"

#pragma GCC diagnostic ignored "-Wshift-count-overflow"

int16_t shift_n_cast(uint8_t high, uint8_t low) {
    return (static_cast<int16_t>(high) << 0x08) + static_cast<int16_t>(low);
}

uint8_t shift_n_set(const Setting& setting, uint8_t current, uint8_t value) {
    return (current & setting.m_write_mask) | (value << setting.m_shift);
}

uint8_t mask_n_shift(const Setting& setting, uint8_t value) {
    return (setting.m_read_mask & value) >> setting.m_shift;
}

void set_list(const int16_t src[], float dst[], float scale) {
    for (size_t idx = 0; idx < 3; idx++) {
        dst[idx] = static_cast<float>(src[idx]) * scale;
    }
}