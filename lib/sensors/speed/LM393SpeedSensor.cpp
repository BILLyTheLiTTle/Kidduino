#include "LM393SpeedSensor.h"

LM393SpeedSensor* LM393SpeedSensor::instance = nullptr;

LM393SpeedSensor::LM393SpeedSensor(uint8_t inputPin,
                                   uint16_t pulsesPerRevolution,
                                   float wheelCircumferenceMeters,
                                   uint32_t debounceMicros)
    : pin(inputPin),
      pulsesPerRev(pulsesPerRevolution),
      wheelCircumference(wheelCircumferenceMeters),
      pulseCount(0),
      lastPulseCount(0),
      lastTime(0),
      rpm(0.0f),
      lastInterruptMicros(0),
      debounceMicros(debounceMicros)
{}

void LM393SpeedSensor::begin() {
    instance = this;

    pinMode(pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(pin), isrWrapper, RISING);

    lastTime = millis();
}

void LM393SpeedSensor::isrWrapper() {
    if (instance) {
        instance->handleInterrupt();
    }
}

void LM393SpeedSensor::handleInterrupt() {
    uint32_t now = micros();

    if (now - lastInterruptMicros >= debounceMicros) {
        pulseCount++;
        lastInterruptMicros = now;
    }
}

void LM393SpeedSensor::update() {
    uint32_t now = millis();
    uint32_t currentPulses = pulseCount;

    uint32_t deltaPulses = currentPulses - lastPulseCount;
    uint32_t deltaTime = now - lastTime; // ms

    if (deltaTime > 0) {
        float revolutions = (float)deltaPulses / pulsesPerRev;
        float seconds = deltaTime / 1000.0f; // 1s = 1000ms

        rpm = (revolutions / seconds) * 60.0f; // 1 minute = 60s
    }

    lastPulseCount = currentPulses;
    lastTime = now;
}

float LM393SpeedSensor::getRPM() {
    return rpm;
}

float LM393SpeedSensor::getRPS() {
    return rpm / 60.0f; // 1 minute = 60s
}

float LM393SpeedSensor::getSpeedMps() {
    return getRPS() * wheelCircumference;
}

float LM393SpeedSensor::getSpeedKmph() {
    return getSpeedMps() * 3.6f; // 1m/s = 3.6 km/h
}

uint32_t LM393SpeedSensor::getPulseCount() {
    return pulseCount;
}