#ifndef __LIB__LSM9DS1_MAG_H__
#define __LIB__LSM9DS1_MAG_H__

#include <Arduino.h>
#include <Wire.h>
#include "helpers.h"
#include "setting.h"
#include "unit.h"
#include "def.h"
#include "i2c.h"

/**
 * @class Mag
 * @brief M unit.
 */
class Mag: public Unit {
  public:
    /**
     * @brief Construct a new Mag object
     *
     * @param i2c_ptr Pointer to #I2C.
     * @param m_range M's range (full scale range).
     * @param m_rate M's rate (Output data rate).
     * @param m_mode M's operating mode.
     * @param addr M's address.
     */
    Mag(I2C* i2c_ptr,
        mag::FSR m_range,
        mag::ODR m_rate,
        mag::OP_MODE m_mode,
        uint8_t addr = mag::ADDRESS);

    /**
     * @brief Check if M's ID is valid.
     *
     * @return true if valid,
     * @return false otherwise.
     */
    bool valid_device_id();

    /**
     * @brief Compute M's current values, in @f$Gauss@f$.
     *
     * @param data Array to hold values.
     * @return true if read,
     * @return false otherwise.
     */
    bool read_m(float data[]);

    /**
     * @brief Reset M.
     *
     * @param config Configuration.
     * @return true if reset,
     * @return false otherwise.
     */
    bool reset(uint8_t config = mag::DEFAULT_CONFIG);

    /**
     * @brief Setup M.
     *
     * @return true if set,
     * @return false otherwise.
     */
    bool setup();

    /**
     * @brief Check for new values.
     *
     * @return true if new values available.
     * @return false otherwise.
     */
    bool available();

  private:
    /**
     * @brief Full scale range.
     */
    mag::FSR fsr;

    /**
     * @brief Output data rate.
     */
    mag::ODR odr;

    /**
     * @brief Operating mode.
     */
    mag::OP_MODE mode;

    /**
     * @brief Retrieve raw data.
     *
     * @param data Array to hold values.
     * @return true if retrieved,
     * @return false otherwise
     */
    bool raw_m(int16_t data[]);
};

#endif /* __LIB__LSM9DS1_MAG_H__ */