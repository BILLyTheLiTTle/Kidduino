#pragma once

#include <Arduino.h>

// High-level rules the system enforces (SAFE vs NORMAL).
// Always get priority from UserSettings
enum SystemSettings {
    NORMAL,
    SAFE
};

// What the user or driver requests (ramp, speed, behavior tweaks). 
// In case system decided to apply SystemSettings for safety then UserSettings will be bypassed
enum UserSettings {
    INSTANT,
    SMOOTH
};

class MotorDriver {
public:
    virtual void forward(uint8_t speed) = 0;
    virtual void backward(uint8_t speed) = 0;
    virtual void coast() = 0;
    virtual void brake() = 0;

    virtual void setMode(SystemSettings mode) = 0;
    virtual void setRamp(UserSettings ramp) = 0;

    virtual ~MotorDriver() {}
};