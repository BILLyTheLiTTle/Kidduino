#pragma once

#include "L293DHalf.h"

class TB6612FNGHalf : public L293DHalf {
public:
    // Constructor just calls base with pins
    TB6612FNGHalf(uint8_t in1, uint8_t in2, uint8_t pwm) 
        : L293DHalf(in1, in2, pwm) {}

    // No need to override anything unless you want different PWM behavior
};