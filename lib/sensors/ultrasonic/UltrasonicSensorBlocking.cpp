#include "UltrasonicSensorBlocking.h"

UltrasonicSensorBlocking::UltrasonicSensorBlocking(uint8_t triggerPin, uint8_t echoPin) {
    _trig = triggerPin;
    _echo = echoPin;
}

void UltrasonicSensorBlocking::begin() {
    pinMode(_trig, OUTPUT);
    pinMode(_echo, INPUT);
    digitalWrite(_trig, LOW);
}

float UltrasonicSensorBlocking::readDistance() {
    // Send trigger pulse
    digitalWrite(_trig, LOW);
    delayMicroseconds(2);

    digitalWrite(_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trig, LOW);

    // Measure pulse duration (blocking)
    unsigned long duration = pulseIn(_echo, HIGH, TIMEOUT);

    if (duration == 0) return -1; // timeout

    // Convert to distance in cm
    return duration * SPEED_OF_SOUND / 2.0f;
}