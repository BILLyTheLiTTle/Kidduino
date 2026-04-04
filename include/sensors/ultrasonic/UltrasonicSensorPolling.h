#pragma once
#include <Arduino.h>

class UltrasonicSensorPolling {
public:
    // Constructor: triggerPin = pin for trigger, echoPin = pin for echo
    UltrasonicSensorPolling(uint8_t triggerPin, uint8_t echoPin);
    
    void begin();
    // Call repeatedly in loop(), returns last measured distance (cm)
    float read();

private:
    uint8_t _trig;
    uint8_t _echo;

    unsigned long _lastTrigger;
    unsigned long _pulseStart;
    unsigned long _pulseEnd;
    bool _waiting;

    float _distance;

    static constexpr float SPEED_OF_SOUND = 0.034; // cm/µs
    static constexpr unsigned long TRIGGER_INTERVAL = 60000UL; // 60 ms

    void _sendTrigger();
};