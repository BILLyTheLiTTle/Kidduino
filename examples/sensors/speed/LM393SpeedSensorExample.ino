#include "LM393SpeedSensor.h"

// pin, pulses per revolution, wheel circumference (meters), debounce (micros)
LM393SpeedSensor sensor(2, 20, 0.21, 500);

unsigned long lastPrint = 0;

void setup() {
    Serial.begin(115200);
    sensor.begin();
}

void loop() {
    sensor.update();

    // print κάθε 500ms (όχι κάθε loop σαν χαμένος)
    if (millis() - lastPrint >= 500) {
        lastPrint = millis();

        Serial.print("RPM: ");
        Serial.print(sensor.getRPM());

        Serial.print(" | RPS: ");
        Serial.print(sensor.getRPS());

        Serial.print(" | m/s: ");
        Serial.print(sensor.getSpeedMps());

        Serial.print(" | km/h: ");
        Serial.println(sensor.getSpeedKmph());
    }
}