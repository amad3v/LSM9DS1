#ifndef __LIB__LSM9DS1_MANAGER_H__
#define __LIB__LSM9DS1_MANAGER_H__

#include <Arduino.h>
#include <Wire.h>

/**
 * @class I2C
 * @brief Manage I2C operations. Wire1 wrapper, from Wire library.
 */
class I2C {
  private:
    /**
     * @brief Wire pointer.
     */
    TwoWire* i2c;

  public:
    /**
     * @brief Construct a new I2C object.
     */
    I2C();

    ~I2C();

    /**
     * @brief Initialize I2C communications.
     */
    void begin();

    /**
     * @brief Read one register.
     *
     * @param unitAddress Unit address, XL/G or M.
     * @param reg Target register.
     * @param data Holds register's content.
     * @return true if read,
     * @return false otherwise.
     */
    bool readRegister(uint8_t unitAddress, uint8_t reg, uint8_t* data);

    /**
     * @brief Read multiple registers.
     *
     * @param unitAddress Unit address, XL/G or M.
     * @param reg Target register.
     * @param data Array to hold registers content.
     * @param sz @p data size.
     * @return true if read,
     * @return false otherwise.
     */
    bool
    readRegisters(uint8_t unitAddress, uint8_t reg, uint8_t* data, size_t sz);

    /**
     * @brief Write register's content.
     *
     * @param unitAddress Unit address, XL/G or M.
     * @param reg Target register.
     * @param value Value to write.
     * @return true if written,
     * @return false otherwise.
     */
    bool writeRegister(uint8_t unitAddress, uint8_t reg, uint8_t value);

    /**
     * @brief Stops communications.
     */
    void end();
};

#endif /* __LIB__LSM9DS1_MANAGER_H__ */