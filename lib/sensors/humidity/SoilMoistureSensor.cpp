#include "SoilMoistureSensor.h"

SoilMoistureSensor::SoilMoistureSensor(uint8_t analogPin)
    : _analogPin(analogPin), _digitalPin(255), _hasDigital(false) {}

SoilMoistureSensor::SoilMoistureSensor(uint8_t analogPin, uint8_t digitalPin)
    : _analogPin(analogPin), _digitalPin(digitalPin), _hasDigital(true) {}

void SoilMoistureSensor::begin() {
    pinMode(_analogPin, INPUT);
    if (_hasDigital) {
        pinMode(_digitalPin, INPUT);
    }
}

int SoilMoistureSensor::readAnalog() const {
    return analogRead(_analogPin);
}

int SoilMoistureSensor::readAverage(uint8_t samples) const {
    long sum = 0;
    for (uint8_t i = 0; i < samples; i++) {
        sum += readAnalog();
        delay(5); // small delay for stability
    }
    return sum / samples;
}

bool SoilMoistureSensor::isWet() const {
    if (_hasDigital) {
        return digitalRead(_digitalPin) == HIGH;
    } else {
        int val = readAverage(); // use averaged reading
        return val > _threshold;
    }
}

void SoilMoistureSensor::setThreshold(int value) {
    _threshold = value;
}

// Non-blocking periodic reading
void SoilMoistureSensor::updatePeriodic(unsigned long intervalMs) {
    unsigned long now = millis();
    if (now - _lastReadTime >= intervalMs) {
        _lastAnalog = readAnalog();
        _lastReadTime = now;
    }
}

// Get last measured analog value
int SoilMoistureSensor::getLastAnalog() const {
    return _lastAnalog;
}