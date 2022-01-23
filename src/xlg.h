#ifndef __LIB__LSM9DS1_DEF_XLG_H__
#define __LIB__LSM9DS1_DEF_XLG_H__

#include <Arduino.h>
#include "helpers.h"
#include "setting.h"
#include "unit.h"
#include "def.h"
#include "i2c.h"
#include "helpers.h"

/**
 * @class XLG
 * @brief XL/G unit.
 */
class XLG: public Unit {
  public:
    /**
     * @brief Construct a new XLG object.
     *
     * @param i2c_ptr Pointer to #I2C.
     * @param xl_range XL's range (full scale range).
     * @param g_range G's range (full scale range).
     * @param xlg_rate XL/G's rate (Output data rate).
     * @param addr XL/G's address.
     */
    XLG(I2C* i2c_ptr,
        xlg::FSR_XL xl_range,
        xlg::FSR_G g_range,
        xlg::ODR xlg_rate,
        uint8_t addr = xlg::ADDRESS);

    /**
     * @brief Check if M's ID is valid.
     *
     * @return true if valid,
     * @return false otherwise.
     */
    bool valid_device_id();

    /**
     * @brief Compute M's current values, in @f$\unitfrac{^{\circ}}{s}@f$.
     *
     * @param data Array to hold values.
     * @return true if read,
     * @return false otherwise.
     */
    bool read_g(float data[]);

    /**
     * @brief Compute M's current values, in @f$g@f$.<br>
     * @f$\unit[1]{g\approx9.81\unitfrac{m}{s^{2}}}@f$
     *
     * @param data Array to hold values.
     * @return true if read,
     * @return false otherwise.
     */
    bool read_xl(float data[]);

    /**
     * @brief Compute M's current values, in @f$^{\circ}@f$.
     *
     * @param data Array to hold values.
     * @return true if read,
     * @return false otherwise.
     */
    bool read_t(float& data);

    /**
     * @brief Reset M.
     *
     * @param config Configuration.
     * @return true if reset,
     * @return false otherwise.
     */
    bool reset(uint8_t config = xlg::DEFAULT_CONFIG);

    /**
     * @brief Setup M.
     *
     * @return true if set,
     * @return false otherwise.
     */
    bool setup();

    /**
     * @brief Check for XL/G new values.
     *
     * @return true if new values available.
     * @return false otherwise.
     */
    bool available();

    /**
     * @brief Check for XL new values.
     *
     * @return true if new values available.
     * @return false otherwise.
     */
    bool xl_available();

    /**
     * @brief Check for G new values.
     *
     * @return true if new values available.
     * @return false otherwise.
     */
    bool g_available();

    /**
     * @brief Check for T new values.
     *
     * @return true if new values available.
     * @return false otherwise.
     */
    bool t_available();

  private:
    /**
     * @brief G full scale range.
     */
    xlg::FSR_G fsr_g;

    /**
     * @brief XL full scale range.
     */
    xlg::FSR_XL fsr_xl;

    /**
     * @brief Output data rate.
     */
    xlg::ODR odr;

    /**
     * @brief Retrieve G raw data.
     *
     * @param data Array to hold values.
     * @return true if retrieved,
     * @return false otherwise
     */
    bool raw_g(int16_t data[]);

    /**
     * @brief Retrieve XL raw data.
     *
     * @param data Array to hold values.
     * @return true if retrieved,
     * @return false otherwise
     */
    bool raw_xl(int16_t data[]);

    /**
     * @brief Retrieve T raw data.
     *
     * @param data Array to hold values.
     * @return true if retrieved,
     * @return false otherwise
     */
    bool raw_t(int16_t data[]);

    /**
     * @brief Read a setting from STATUS_REG_1.
     *
     * @param mask Setting's mask.
     * @return true if read,
     * @return false otherwise.
     */
    bool status(uint8_t mask);
};

#endif /* __LIB__LSM9DS1_DEF_XLG_H__ */