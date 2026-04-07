#include "L293DHalf.h"

// Pins for L293DHalf: IN1, IN2, EN
L293DHalf motor(3, 4, 5);

void setup() {
    Serial.begin(9600);

    // System enforces SAFE mode
    motor.setMode(SystemSettings::SAFE);

    // User chooses ramp behavior (ignored if SAFE overrides)
    motor.setRamp(UserSettings::SMOOTH);

    Serial.println("Single motor ready");
}

void loop() {
    Serial.println("Forward 100%");
    motor.forward(100);
    delay(3000);

    Serial.println("Slow backward 50%");
    motor.backward(50);
    delay(3000);

    Serial.println("Brake");
    motor.brake();
    delay(2000);

    Serial.println("Coast");
    motor.coast();
    delay(2000);
}