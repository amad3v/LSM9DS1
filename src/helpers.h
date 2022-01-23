/**
 * @file helpers.h
 * @date 23.01.22
 * @author amad3v (amad3v@gmail.com)
 * @version 1.0.1
 *
 * @brief Helper functions.
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

#ifndef __LIB__LSM9DS1_HELPERS_H__
#define __LIB__LSM9DS1_HELPERS_H__

#include <Arduino.h>
#include "setting.h"
#include "def.h"

/**
 * @brief Construct 16-bit signed integer from 16-bit word 2's complement.
 *
 * @param high MSB byte.
 * @param low LSB byte.
 * @return 16-bit signed integer.
 */
int16_t shift_n_cast(uint8_t high, uint8_t low);

/**
 * @brief Compute register's new value to change a setting (less than 8 bits).
 *
 * @param setting Setting to update.
 * @param current Current register's content.
 * @param value New setting's value.
 * @return New register's content.
 */
uint8_t shift_n_set(const Setting& setting, uint8_t current, uint8_t value);

/**
 * @brief Compute setting value
 *
 * @param setting Setting to read.
 * @param value Current register's content.
 * @return Setting's value.
 */
uint8_t mask_n_shift(const Setting& setting, uint8_t value);

/**
 * @brief Scale given array.
 *
 * @param src Array source [raw values].
 * @param dst Array destination [computed values].
 * @param scale Scale factor.
 */
void set_list(const int16_t src[], float dst[], float scale);

#endif /* __LIB__LSM9DS1_HELPERS_H__ */