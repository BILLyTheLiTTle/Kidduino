#pragma once

#include "MotorDriver.h"
#include <Arduino.h>

class BTS7960 : public MotorDriver {
private:
    uint8_t RPWM, LPWM, R_EN, L_EN;

    SystemSettings mode = NORMAL;
    UserSettings ramp = INSTANT;

    uint8_t currentPWM = 0;

    uint8_t mapSpeed(uint8_t speed); // optional mapping
    void applyPWM(uint8_t targetPWM, bool forwardDirection, UserSettings effectiveRamp);

public:
    BTS7960(uint8_t RPWM, uint8_t LPWM, uint8_t R_EN, uint8_t L_EN);

    void forward(uint8_t speed) override;
    void backward(uint8_t speed) override;
    void coast() override;
    void brake() override;

    void setMode(SystemSettings m) override;
    void setRamp(UserSettings r) override;
};