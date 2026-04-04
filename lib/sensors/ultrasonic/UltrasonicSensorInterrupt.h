#pragma once
#include <Arduino.h>

class UltrasonicSensorInterrupt {
public:
    UltrasonicSensorInterrupt(uint8_t triggerPin, uint8_t echoPin);

    void begin();
    void update();        // non-blocking
    float read();         // returns last distance (cm)

private:
    uint8_t _trig;
    uint8_t _echo;

    volatile unsigned long _start;
    volatile unsigned long _end;
    volatile bool _ready;

    unsigned long _lastTrigger;
    float _distance;

    static UltrasonicSensorInterrupt* _instance;

    static void _isrStatic();
    void _isr();
};