#include <UltrasonicSensorBlocking.h>

// Create a sensor object: TRIG = pin 4, ECHO = pin 3
UltrasonicSensorBlocking sensor(4, 3);

void setup() {
    Serial.begin(9600);    // start serial monitor
    sensor.begin();        // initialize pins
}

void loop() {
    float distance = sensor.readDistance();  // blocking call
    if (distance < 0) {
        Serial.println("No echo detected (timeout)");
    } else {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
    }

    delay(500);  // small delay before next reading
}