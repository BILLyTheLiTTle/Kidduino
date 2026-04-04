#include <UltrasonicSensorPolling.h>

// TRIG = pin 4, ECHO = pin 3
UltrasonicSensorPolling sensor(4, 3);

void setup() {
    Serial.begin(9600);
    sensor.begin();   // initialize pins
}

void loop() {
    float distance = sensor.read();  // non-blocking, returns last value

    if (distance >= 0) {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
    } else {
        Serial.println("Waiting for first measurement...");
    }

    // You can do other tasks here without blocking
    delay(100); // optional small delay for readability
}