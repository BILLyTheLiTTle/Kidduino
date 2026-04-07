#include "L293DFull.h"

static const uint8_t MIN_PWM = 5;
static const uint8_t MAX_PWM = 255;

L293DFull::L293DFull(uint8_t pinIn1, uint8_t pinIn2, uint8_t pinEn1,
                     uint8_t pinIn3, uint8_t pinIn4, uint8_t pinEn2)
    : in1(pinIn1), in2(pinIn2), en1(pinEn1),
      in3(pinIn3), in4(pinIn4), en2(pinEn2),
      mode(NORMAL), ramp(INSTANT), pwmA(0), pwmB(0) {

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(en1, OUTPUT);

    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(en2, OUTPUT);

    coast();
}

uint8_t L293DFull::mapSpeed(uint8_t speed) {
    speed = constrain(speed, 0, 100);
    if (speed == 0) return 0;
    return map(speed, 1, 100, MIN_PWM, MAX_PWM);
}

void L293DFull::applyPWM(uint8_t targetPWM, UserSettings effectiveRamp) {

    if (effectiveRamp == INSTANT) {
        pwmA = pwmB = targetPWM;
    } else {
        if (pwmA < targetPWM) pwmA++;
        else if (pwmA > targetPWM) pwmA--;

        if (pwmB < targetPWM) pwmB++;
        else if (pwmB > targetPWM) pwmB--;
    }
    pwmA = constrain(pwmA, 0, 255);
    pwmB = constrain(pwmB, 0, 255);

    analogWrite(en1, pwmA);
    analogWrite(en2, pwmB);
}

void L293DFull::forward(uint8_t speed) {

    if (speed == 0) {
        coast();
        return;
    }

    UserSettings effectiveRamp = (mode == SAFE) ? SMOOTH : ramp;

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    applyPWM(mapSpeed(speed), effectiveRamp);
}

void L293DFull::backward(uint8_t speed) {

    if (speed == 0) {
        coast();
        return;
    }

    UserSettings effectiveRamp = (mode == SAFE) ? SMOOTH : ramp;

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    applyPWM(mapSpeed(speed), effectiveRamp);
}

void L293DFull::coast() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    analogWrite(en1, 0);
    analogWrite(en2, 0);

    pwmA = pwmB = 0;
}

void L293DFull::brake() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);

    analogWrite(en1, MAX_PWM);
    analogWrite(en2, MAX_PWM);

    pwmA = pwmB = MAX_PWM;
}

void L293DFull::setMode(SystemSettings m) {
    mode = m;
}

void L293DFull::setRamp(UserSettings r) {
    ramp = r;
}