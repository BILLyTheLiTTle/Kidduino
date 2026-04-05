#include "RgbLedDriver.h"

RgbLedDriver::RgbLedDriver(uint8_t redPin, uint8_t greenPin, uint8_t bluePin)
    : _redPin(redPin), _greenPin(greenPin), _bluePin(bluePin),
      _state(false), _lastToggle(0), _currentColor(Color::OFF()) {}

void RgbLedDriver::begin() {
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);
    _applyColor();
}

void RgbLedDriver::setColor(const Color& color) {
    _currentColor = color;
    _state = !(color.r == 0 && color.g == 0 && color.b == 0);
    _applyColor();
}

void RgbLedDriver::_applyColor() {
    analogWrite(_redPin, _state ? _currentColor.r : 0);
    analogWrite(_greenPin, _state ? _currentColor.g : 0);
    analogWrite(_bluePin, _state ? _currentColor.b : 0);
}

void RgbLedDriver::off() {
    analogWrite(_redPin, 0);
    analogWrite(_greenPin, 0);
    analogWrite(_bluePin, 0);
}

void RgbLedDriver::toggle() {
    _state = !_state;
    _applyColor();
}

void RgbLedDriver::autoToggle(unsigned long interval) {
    unsigned long now = millis();
    if (now - _lastToggle >= interval) {
        toggle();
        _lastToggle = now;
    }
}