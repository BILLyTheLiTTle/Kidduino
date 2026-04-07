#include "L293DHalf.h"

static const uint8_t MIN_PWM = 5;
static const uint8_t MAX_PWM = 255;

L293DHalf::L293DHalf(uint8_t pinIn1, uint8_t pinIn2, uint8_t pinEn)
    : in1(pinIn1), in2(pinIn2), en(pinEn),
      mode(NORMAL), ramp(INSTANT), currentPWM(0) {

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(en, OUTPUT);

    coast();
}

uint8_t L293DHalf::mapSpeed(uint8_t speed) {
    speed = constrain(speed, 0, 100);
    if (speed == 0) return 0;
    return map(speed, 1, 100, MIN_PWM, MAX_PWM);
}

void L293DHalf::applyPWM(uint8_t targetPWM, UserSettings effectiveRamp) {
    if (effectiveRamp == INSTANT) {
        currentPWM = targetPWM;
    } else {
        if (currentPWM < targetPWM) currentPWM++;
        else if (currentPWM > targetPWM) currentPWM--;
    }
    currentPWM = constrain(currentPWM, 0, 255);

    analogWrite(en, currentPWM);
}

void L293DHalf::forward(uint8_t speed) {

    if (speed == 0) {
        coast();
        return;
    }

    UserSettings effectiveRamp = (mode == SAFE) ? SMOOTH : ramp;

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    applyPWM(mapSpeed(speed), effectiveRamp);
}

void L293DHalf::backward(uint8_t speed) {

    if (speed == 0) {
        coast();
        return;
    }

    UserSettings effectiveRamp = (mode == SAFE) ? SMOOTH : ramp;

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    applyPWM(mapSpeed(speed), effectiveRamp);
}

void L293DHalf::coast() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(en, 0);
    currentPWM = 0;
}

void L293DHalf::brake() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    analogWrite(en, MAX_PWM);
    currentPWM = MAX_PWM;
}

void L293DHalf::setMode(SystemSettings m) {
    mode = m;
}

void L293DHalf::setRamp(UserSettings r) {
    ramp = r;
}