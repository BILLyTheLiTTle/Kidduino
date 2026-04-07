#pragma once

#include "MotorDriver.h"

class L293DHalf : public MotorDriver {
private:
    uint8_t in1, in2, en;

    SystemSettings mode;
    UserSettings ramp;

    uint8_t currentPWM;

    uint8_t mapSpeed(uint8_t speed);
    void applyPWM(uint8_t targetPWM, UserSettings effectiveRamp);

public:
    L293DHalf(uint8_t pinIn1, uint8_t pinIn2, uint8_t pinEn);

    void forward(uint8_t speed) override;
    void backward(uint8_t speed) override;
    void coast() override;
    void brake() override;

    void setMode(SystemSettings m) override;
    void setRamp(UserSettings r) override;
};