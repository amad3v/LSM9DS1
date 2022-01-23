/**
 * @file setting.h
 * @date 23.01.22
 * @author amad3v (amad3v@gmail.com)
 * @version 1.0.1
 *
 * @brief Register settings.
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

#ifndef __LIB__LSM9DS1_SETTING_H__
#define __LIB__LSM9DS1_SETTING_H__

#pragma GCC diagnostic ignored "-Wnarrowing"

#include <Arduino.h>

/**
 * @class Setting
 * @brief Register's setting properties
 */
class Setting {
  public:
    /**
     * @brief Mask used when reading.
     */
    uint8_t m_read_mask;

    /**
     * @brief Mask used when writing.
     */
    uint8_t m_write_mask;

    /**
     * @brief Number of positions to shift.
     */
    uint8_t m_shift;

    /**
     * @brief Construct a new Setting object.
     *
     * @param t_read_mask Reading mask.
     * @param t_shift Number of positions to shift.
     */
    explicit Setting(uint8_t t_read_mask, uint8_t t_shift = 0) :
        m_read_mask { t_read_mask },
        m_write_mask { 0xff ^ t_read_mask },
        m_shift { t_shift } {}
};

#endif /* __LIB__LSM9DS1_SETTING_H__ */