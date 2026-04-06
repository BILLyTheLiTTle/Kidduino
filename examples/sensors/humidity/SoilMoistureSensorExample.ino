#include <Arduino.h>
#include "SoilMoistureSensor.h"

// Pin definitions
const uint8_t SOIL_ANALOG_PIN = A0;  // analog pin connected to sensor
const uint8_t LED_PIN = 13;          // onboard LED
const uint8_t SOIL_DIGITAL_PIN = 2;  // optional digital threshold pin

// Create sensor object (analog only or with digital pin)
SoilMoistureSensor soil(SOIL_ANALOG_PIN);  
//SoilMoistureSensor soil(SOIL_ANALOG_PIN, SOIL_DIGITAL_PIN); // uncomment if using digital

void setup() {
    Serial.begin(9600);
    soil.begin();
    pinMode(LED_PIN, OUTPUT);

    // Optional: set custom threshold for dry/wet
    soil.setThreshold(550); // adjust to your soil
}

void loop() {
    // Read averaged analog value
    int moistureValue = soil.readAverage(10); // 10 samples

    // Print it
    Serial.print("Soil analog value: ");
    Serial.println(moistureValue);

    // Determine wet/dry
    if (soil.isWet()) {
        digitalWrite(LED_PIN, HIGH); // wet → LED on
        Serial.println("Soil is WET");
    } else {
        digitalWrite(LED_PIN, LOW); // dry → LED off
        Serial.println("Soil is DRY");
    }

    delay(1000); // 1 second between readings
}