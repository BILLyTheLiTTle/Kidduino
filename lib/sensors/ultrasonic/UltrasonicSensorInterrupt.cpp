#include "UltrasonicSensorInterrupt.h"

UltrasonicSensorInterrupt* UltrasonicSensorInterrupt::_instance = nullptr;

UltrasonicSensorInterrupt::UltrasonicSensorInterrupt(uint8_t triggerPin, uint8_t echoPin) {
    // assign pins
    _trig = triggerPin;
    _echo = echoPin;

    // init measurement variables
    _start = 0;
    _end = 0;
    _ready = false;
    _lastTrigger = 0;
    _distance = -1.0f;

    // check interrupt pin
    int irqNum = digitalPinToInterrupt(_echo);
    if (irqNum == NOT_AN_INTERRUPT) {
        Serial.print("Error: Pin ");
        Serial.print(_echo);
        Serial.print(" cannot be used for interrupts! ");
        Serial.println("Try using Pin 2 or Pin 3 instead!");
        return; // fail-safe, don’t attach ISR
    }

    // point static instance to this object for ISR
    _instance = this;
}

void UltrasonicSensorInterrupt::begin() {
    pinMode(_trig, OUTPUT);
    pinMode(_echo, INPUT);
    digitalWrite(_trig, LOW);

    attachInterrupt(digitalPinToInterrupt(_echo), _isrStatic, CHANGE);
}

void UltrasonicSensorInterrupt::update() {
    unsigned long now = millis();

    // trigger every 50ms
    if (now - _lastTrigger >= 50) {
        digitalWrite(_trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(_trig, LOW);
        _lastTrigger = now;
    }

    if (_ready) {
        detachInterrupt(digitalPinToInterrupt(_echo)); //noInterrupts();
        unsigned long duration = _end - _start;
        _ready = false;
        attachInterrupt(digitalPinToInterrupt(_echo), _isrStatic, CHANGE); //interrupts();

        _distance = duration * 0.034 / 2;
    }
}

float UltrasonicSensorInterrupt::read() {
    return _distance;
}

void UltrasonicSensorInterrupt::_isrStatic() {
    if (_instance) _instance->_isr();
}

void UltrasonicSensorInterrupt::_isr() {
    if (digitalRead(_echo) == HIGH) {
        _start = micros();
    } else {
        _end = micros();
        _ready = true;
    }
}