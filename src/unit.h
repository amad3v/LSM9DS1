#ifndef __LIB__LSM9DS1_UNIT_H__
#define __LIB__LSM9DS1_UNIT_H__

#include <Arduino.h>
#include "i2c.h"
#include "setting.h"
#include "helpers.h"

/**
 * @brief Abstract class for #XLG/#Mag.
 */
class Unit {
  protected:
    /**
     * @brief Construct a new Unit object.
     *
     * @param i2c_ptr I2C pointer.
     * @param addr Unit's address.
     */
    Unit(I2C* i2c_ptr, uint8_t addr);
    virtual ~Unit() {};

    /**
     * @brief Read register(s) content.
     *
     * @param reg Register to read from / Starting register.
     * @param data Holds register(s) content
     * @param sz Size of @p data
     * @return true if read,
     * @return false otherwise.
     */
    bool read(uint8_t reg, uint8_t* data, size_t sz = 1);

    /**
     * @brief Write to register.
     *
     * @param reg Register to write to.
     * @param value Value to write.
     * @return true if written,
     * @return false otherwise.
     */
    bool write(uint8_t reg, uint8_t value);

    /**
     * @brief Read raw values from registers.<br>
     * Used to read axes values.
     *
     * @param reg Starting register.
     * @param data Array of size 3 to hold data.
     * @return true if read,
     * @return false otherwise.
     */
    bool raw_value(uint8_t reg, int16_t* data);

    /**
     * @brief Virtual method.
     * @see #XLG/#Mag
     */
    virtual bool valid_device_id() = 0;

    /**
     * @brief Virtual method.
     * @see #XLG/#Mag
     */
    virtual bool reset(uint8_t config) = 0;

    /**
     * @brief Virtual method.
     * @see #XLG/#Mag
     */
    virtual bool setup() = 0;

  private:
    /**
     * @brief I2C communications manager.
     */
    I2C* i2c;

    /**
     * @brief Unit's address.
     */
    const uint8_t address;
};

#endif /* __LIB__LSM9DS1_UNIT_H__ */