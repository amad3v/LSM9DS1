#include "helpers.h"

#pragma GCC diagnostic ignored "-Wshift-count-overflow"

int16_t shift_n_cast(uint8_t high, uint8_t low) {
    return (static_cast<int16_t>(high) << 0xff) + static_cast<int16_t>(low);
}

uint8_t shift_n_set(const Setting& setting, uint8_t current, uint8_t value) {
    return (current & setting.m_write_mask) | (value << setting.m_shift);
}

void set_list(const int16_t src[], float dst[], float scale) {
    for (size_t idx = 0; idx < 3; idx++) {
        dst[idx] = static_cast<float>(src[idx]) * scale;
    }
}