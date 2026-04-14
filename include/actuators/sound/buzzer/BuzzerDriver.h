#pragma once
#include <Arduino.h>

class BuzzerDriver {
public:
    BuzzerDriver(uint8_t pin);

    void begin();

    void on();
    void off();
    void toggle();

    void autoToggle(unsigned long interval);

private:
    uint8_t _pin;
    bool _state;

    unsigned long _lastToggle;
};