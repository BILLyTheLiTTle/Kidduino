#include "L293DFull.h"

// Pins for L293DFull: IN1, IN2, EN1, IN3, IN4, EN2
L293DFull motorPair(3, 4, 5, 6, 7, 8);

void setup() {
    Serial.begin(9600);

    // System settings
    motorPair.setMode(SystemSettings::SAFE);

    // User settings
    motorPair.setRamp(UserSettings::SMOOTH);

    Serial.println("Dual motor ready");
}

void loop() {
    Serial.println("Forward full speed");
    motorPair.forward(100);
    delay(3000);

    Serial.println("Backward half speed");
    motorPair.backward(50);
    delay(3000);

    Serial.println("Brake both motors");
    motorPair.brake();
    delay(2000);

    Serial.println("Coast both motors");
    motorPair.coast();
    delay(2000);
}