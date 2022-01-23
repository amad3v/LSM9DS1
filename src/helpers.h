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
 * @brief Scale given array.
 *
 * @param src Array source [raw values].
 * @param dst Array destination [computed values].
 * @param scale Scale factor.
 */
void set_list(const int16_t src[], float dst[], float scale);

#endif /* __LIB__LSM9DS1_HELPERS_H__ */