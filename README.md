# LSMDS1 Documentation

### 1. Intro

Sensor driver for LSM9DS1 sensor using I2C.
Mainly written to use with Arduino Nano 33 BLE.
This is the first commit covering only basic functionalities.

### 2. Features

- Set range and rate \[accelerometer (XLG), gyroscope (XLG) and magnetometer (Mag)].
- Read values in default units \[accelerometer (`g`), gyroscope (`dps`) and magnetometer (`Gauss`)].
- Read sensor's temperature in \[not to use as reference] `celcius`.

### 3. Abbreviations

- XL: Accelerometer.
- G: Gyroscope.
- M: Magnetometer.
- T: Temperature.
- N/A: Not Applicable.

### 4. Usage

```c++
#include "lsm9ds1.h"

Sensor marg { xlg::FSR_XL::G_8,
              xlg::FSR_G::DPS_500,
              mag::FSR::GAUSS_8,
              xlg::ODR::R_476,
              mag::ODR::R_20 };

void setup() {
    // ...

    if (!marg.begin()) {
        // "Reading sensor failed!"
        while (true) {
            /* code */
        }
    }

    // ...
}

void loop() {
    // ...

    if (marg.available()) {
        float a[3] {}, g[3] {}, m[3] {}, t {};

        marg.read(a, g, m);
        marg.xlgSensor.read_t(t);

        // ...
    }

    // ...
}
```
