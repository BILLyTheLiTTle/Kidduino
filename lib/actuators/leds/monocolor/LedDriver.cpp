#include "LedDriver.h"

LedDriver::Led(uint8_t pin)
    : _pin(pin), _state(false), _lastToggle(0) {}

void LedDriver::begin() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void LedDriver::on() {
    _state = true;
    digitalWrite(_pin, HIGH);
}

void LedDriver::off() {
    _state = false;
    digitalWrite(_pin, LOW);
}

void LedDriver::toggle() {
    _state = !_state;
    digitalWrite(_pin, _state ? HIGH : LOW);
}

void LedDriver::autoToggle(unsigned long interval) {
    unsigned long now = millis();

    if (now - _lastToggle >= interval) {
        toggle();
        _lastToggle = now;
    }
}