#include "UltrasonicSensorPolling.h"

UltrasonicSensorPolling::UltrasonicSensorPolling(uint8_t triggerPin, uint8_t echoPin) {
    _trig = triggerPin;
    _echo = echoPin;
    _lastTrigger = 0;
    _pulseStart = 0;
    _pulseEnd = 0;
    _waiting = false;
    _distance = -1.0f;
}

void UltrasonicSensorPolling::begin() {
    pinMode(_trig, OUTPUT);
    pinMode(_echo, INPUT);
    digitalWrite(_trig, LOW);

}

void UltrasonicSensorPolling::_sendTrigger() {
    digitalWrite(_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trig, LOW);
    _pulseStart = 0; // reset start
    _waiting = true;
}

float UltrasonicSensorPolling::read() {
    unsigned long now = micros();

    // Trigger new pulse if enough time passed
    if (!_waiting && now - _lastTrigger >= TRIGGER_INTERVAL) {
        _sendTrigger();
        _lastTrigger = now;
    }

    // Check for pulse measurement
    if (_waiting) {
        if (digitalRead(_echo) == HIGH && _pulseStart == 0) {
            _pulseStart = micros();
        } else if (digitalRead(_echo) == LOW && _pulseStart != 0) {
            _pulseEnd = micros();
            unsigned long duration = _pulseEnd - _pulseStart;
            _distance = duration * SPEED_OF_SOUND / 2.0f;
            _pulseStart = 0;
            _waiting = false;
        }
    }

    return _distance;
}