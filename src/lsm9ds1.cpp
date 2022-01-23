#include "lsm9ds1.h"

Sensor::Sensor(
    xlg::FSR_XL xl_range,
    xlg::FSR_G g_range,
    mag::FSR m_range,
    xlg::ODR xlg_rate,
    mag::ODR m_rate,
    mag::OP_MODE m_mode) :
    comms { I2C {} },
    xlgSensor { &comms, xl_range, g_range, xlg_rate },
    mSensor { &comms, m_range, m_rate, m_mode } {}

bool Sensor::begin() {
    comms.begin();
    if (!(xlgSensor.valid_device_id() && xlgSensor.reset() && xlgSensor.setup()
          && mSensor.valid_device_id() && mSensor.reset() && mSensor.setup())) {
        comms.end();
        return false;
    }

    return true;
}

bool Sensor::available() {
    return xlgSensor.available() && mSensor.available();
}

bool Sensor::read(float xl[], float g[], float m[]) {
    return (xlgSensor.read_xl(xl) && xlgSensor.read_g(g) && mSensor.read_m(m));
}