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