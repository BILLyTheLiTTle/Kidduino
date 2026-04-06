#pragma once

#include <Arduino.h>

class SoilMoistureSensor {
public:
    // Constructor for analog-only sensor
    SoilMoistureSensor(uint8_t analogPin);

    // Constructor with digital threshold pin
    SoilMoistureSensor(uint8_t analogPin, uint8_t digitalPin);

    // Initialize the sensor (call in setup)
    void begin();

    // Returns raw analog value (0-1023)
    int readAnalog() const;

    // Returns averaged analog value (default 10 samples)
    int readAverage(uint8_t samples = 10) const;

    // Returns true if soil is wet according to digital pin or analog threshold
    bool isWet() const;

    // Set analog threshold for wet/dry
    void setThreshold(int value);

    // Non-blocking periodic reading
    void updatePeriodic(unsigned long intervalMs);
    int getLastAnalog() const;

private:
    uint8_t _analogPin;
    uint8_t _digitalPin;
    bool _hasDigital;
    int _threshold = 500; // default

    // For periodic reading
    int _lastAnalog;
    unsigned long _lastReadTime;
};