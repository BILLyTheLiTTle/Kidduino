#pragma once

#include <Arduino.h>

class LM393SpeedSensor {
private:
    uint8_t pin;
    uint16_t pulsesPerRev;
    float wheelCircumference; // meters

    volatile uint32_t pulseCount;

    uint32_t lastPulseCount;
    uint32_t lastTime;

    float rpm;

    // debounce
    volatile uint32_t lastInterruptMicros;
    uint32_t debounceMicros;

    static LM393SpeedSensor* instance;

    static void isrWrapper();
    void handleInterrupt();

public:
    LM393SpeedSensor(uint8_t pin,
                     uint16_t pulsesPerRev,
                     float wheelCircumference,
                     uint32_t debounceMicros = 500);

    void begin();
    void update();

    float getRPM();
    float getRPS();
    float getSpeedMps();
    float getSpeedKmph();

    uint32_t getPulseCount();
};