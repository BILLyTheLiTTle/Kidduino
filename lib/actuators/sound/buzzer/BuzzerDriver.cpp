#include "BuzzerDriver.h"

BuzzerDriver::BuzzerDriver(uint8_t pin)
    : _pin(pin), _state(false), _lastToggle(0) {}

void BuzzerDriver::begin() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void BuzzerDriver::on() {
    _state = true;
    digitalWrite(_pin, HIGH);
}

void BuzzerDriver::off() {
    _state = false;
    digitalWrite(_pin, LOW);
}

void BuzzerDriver::toggle() {
    _state = !_state;
    digitalWrite(_pin, _state ? HIGH : LOW);
}

void BuzzerDriver::autoToggle(unsigned long interval) {
    unsigned long now = millis();

    if (now - _lastToggle >= interval) {
        toggle();
        _lastToggle = now;
    }
}