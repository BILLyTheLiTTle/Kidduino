#pragma once
#include <Arduino.h>

class UltrasonicSensorBlocking {
public:
    UltrasonicSensorBlocking(uint8_t triggerPin, uint8_t echoPin);

    void begin();

    // Blocking call, returns distance in cm
    float readDistance();

private:
    uint8_t _trig;
    uint8_t _echo;

    static constexpr float SPEED_OF_SOUND = 0.034; // cm/µs
    static constexpr unsigned long TIMEOUT = 30000; // µs
};