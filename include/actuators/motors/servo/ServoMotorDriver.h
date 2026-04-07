#pragma once
#include <Arduino.h>
#include <Servo.h>

class ServoMotorDriver {
private:
    Servo _servo;
    uint8_t _pin;
    int _currentAngle;
    int _targetAngle;
    int _step;
    unsigned long _lastMove;
    unsigned long _intervalMs;

    void _applyStep(); // internal helper

public:
    ServoMotorDriver(uint8_t pin);

    void begin();

    // Immediate absolute move
    void setAngle(int angle);

    // Get current angle
    int getAngle() const;

    // Gradual periodic absolute move
    void setAnglePeriodically(int angle, unsigned long intervalMs);

    // Relative clockwise
    void moveClockwise(int degrees);                        // immediate
    void moveClockwisePeriodically(int degrees, unsigned long intervalMs);  // gradual

    // Relative counterclockwise
    void moveCounterClockwise(int degrees);                        // immediate
    void moveCounterClockwisePeriodically(int degrees, unsigned long intervalMs);  // gradual

    // This is now internal; no need to call separately
    // void updateIfNeeded();
};