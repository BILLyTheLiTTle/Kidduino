#pragma once
#include "L293DFull.h"

class TB6612FNGFull : public L293DFull {
public:
    // Constructor calls base with pin mapping
    TB6612FNGFull(uint8_t in1A, uint8_t in2A, uint8_t pwmA,
                        uint8_t in1B, uint8_t in2B, uint8_t pwmB)
        : L293DFull(in1A, in2A, pwmA, in1B, in2B, pwmB) {}

    // No need to override anything unless PWM behavior differs
};