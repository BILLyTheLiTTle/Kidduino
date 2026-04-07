#include "BTS7960.h"

static const uint8_t MIN_PWM = 50;
static const uint8_t MAX_PWM = 255;

BTS7960::BTS7960(uint8_t RPWM, uint8_t LPWM, uint8_t R_EN, uint8_t L_EN)
    : RPWM(RPWM), LPWM(LPWM), R_EN(R_EN), L_EN(L_EN), currentPWM(0), mode(SystemSettings::NORMAL), ramp(UserSettings::INSTANT)
{
    pinMode(RPWM, OUTPUT);
    pinMode(LPWM, OUTPUT);
    pinMode(R_EN, OUTPUT);
    pinMode(L_EN, OUTPUT);

    digitalWrite(R_EN, HIGH);
    digitalWrite(L_EN, HIGH);

    analogWrite(RPWM, 0);
    analogWrite(LPWM, 0);
}

// Convert 0-100 speed to PWM
uint8_t BTS7960::mapSpeed(uint8_t speed) {
    speed = constrain(speed, 0, 100);
    if (speed == 0) return 0;
    return map(speed, 1, 100, MIN_PWM, MAX_PWM);
}

// Apply PWM with ramping, working only in the loop of Arduino
void BTS7960::applyPWM(uint8_t targetPWM, bool forwardDirection, UserSettings effectiveRamp) {
    if (effectiveRamp == UserSettings::INSTANT) {
        if (forwardDirection) {
            analogWrite(RPWM, targetPWM);
            analogWrite(LPWM, 0);
        } else {
            analogWrite(RPWM, 0);
            analogWrite(LPWM, targetPWM);
        }
        currentPWM = targetPWM;
    } else {
        if (currentPWM < targetPWM) currentPWM++;
        if (currentPWM > targetPWM) currentPWM--;
        currentPWM = constrain(currentPWM, 0, 255);

        if (forwardDirection) {
            analogWrite(RPWM, currentPWM);
            analogWrite(LPWM, 0);
        } else {
            analogWrite(RPWM, 0);
            analogWrite(LPWM, currentPWM);
        }
    }
}

// Forward
void BTS7960::forward(uint8_t speed) {
    if (speed == 0) {
         coast();
         return;
        }

    UserSettings effectiveRamp = (mode == SAFE) ? SMOOTH : ramp;
    
    applyPWM(mapSpeed(speed), true, effectiveRamp);
}

// Backward
void BTS7960::backward(uint8_t speed) {
    if (speed == 0) {
        coast();
        return;
    }

    UserSettings effectiveRamp = (mode == SAFE) ? SMOOTH : ramp;
    
    applyPWM(mapSpeed(speed), false, effectiveRamp);
}

// Coast
void BTS7960::coast() {
    analogWrite(RPWM, 0);
    analogWrite(LPWM, 0);
    currentPWM = 0;
}

// Brake
void BTS7960::brake() {
    // Both low to short motor terminals
    analogWrite(R_EN, 0);
    analogWrite(L_EN, 0);
    currentPWM = 0;
}

// Set system mode
void BTS7960::setMode(SystemSettings m) { mode = m; }

// Set user ramp
void BTS7960::setRamp(UserSettings r) { ramp = r; }