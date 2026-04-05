#pragma once
#include <Arduino.h>
#include "Color.h"

class RgbLedDriver {
public:
    RgbLedDriver(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);

    void begin();
    void setColor(const Color& color);
    void toggle();
    void off();
    void autoToggle(unsigned long interval);

private:
    uint8_t _redPin, _greenPin, _bluePin;
    bool _state;
    unsigned long _lastToggle;
    Color _currentColor;

    void _applyColor();
};