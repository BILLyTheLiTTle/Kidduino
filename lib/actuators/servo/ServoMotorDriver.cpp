#include "ServoMotorDriver.h"

ServoMotorDriver::ServoMotorDriver(uint8_t pin)
    : _pin(pin), _currentAngle(0), _targetAngle(0),
      _step(0), _lastMove(0), _intervalMs(0) {}

void ServoMotorDriver::begin() {
    _servo.attach(_pin);
    _servo.write(_currentAngle);
}

void ServoMotorDriver::setAngle(int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;
    _currentAngle = angle;
    _targetAngle = angle;
    _step = 0;
    _servo.write(_currentAngle);
}

int ServoMotorDriver::getAngle() const {
    return _currentAngle;
}

// Internal step application
void ServoMotorDriver::_applyStep() {
    if (_currentAngle == _targetAngle || _step == 0) return;

    unsigned long now = millis();
    if (now - _lastMove >= _intervalMs) {
        _currentAngle += _step;

        if ((_step > 0 && _currentAngle > _targetAngle) ||
            (_step < 0 && _currentAngle < _targetAngle)) {
            _currentAngle = _targetAngle;
            _step = 0;
        }

        _servo.write(_currentAngle);
        _lastMove = now;
    }
}

// Gradual periodic absolute move
void ServoMotorDriver::setAnglePeriodically(int angle, unsigned long intervalMs) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    _targetAngle = angle;
    _step = (_targetAngle > _currentAngle) ? 1 : -1;
    _intervalMs = intervalMs;

    // Immediately apply a step if enough time has passed
    _applyStep();
}

// Relative clockwise
void ServoMotorDriver::moveClockwise(int degrees) {
    setAngle(_currentAngle + degrees);
}

void ServoMotorDriver::moveClockwisePeriodically(int degrees, unsigned long intervalMs) {
    setAnglePeriodically(_currentAngle + degrees, intervalMs);
}

// Relative counterclockwise
void ServoMotorDriver::moveCounterClockwise(int degrees) {
    setAngle(_currentAngle - degrees);
}

void ServoMotorDriver::moveCounterClockwisePeriodically(int degrees, unsigned long intervalMs) {
    setAnglePeriodically(_currentAngle - degrees, intervalMs);
}

// Public function called internally by periodic functions
// void ServoMotorDriver::updateIfNeeded() {
//     _applyStep();
// }