#pragma once

#include "MotorDriver.h"

class L293DFull : public MotorDriver {
private:
    uint8_t in1, in2, en1;
    uint8_t in3, in4, en2;

    SystemSettings mode;
    UserSettings ramp;

    uint8_t pwmA;
    uint8_t pwmB;

    uint8_t mapSpeed(uint8_t speed);
    void applyPWM(uint8_t targetPWM, UserSettings effectiveRamp);

public:
    L293DFull(uint8_t pinIn1, uint8_t pinIn2, uint8_t pinEn1,
              uint8_t pinIn3, uint8_t pinIn4, uint8_t pinEn2);

    void forward(uint8_t speed) override;
    void backward(uint8_t speed) override;
    void coast() override;
    void brake() override;

    void setMode(SystemSettings m) override;
    void setRamp(UserSettings r) override;
};