#include "ServoMotorDriver.h"

ServoMotorDriver servo(9);

void setup() {
    servo.begin();
    servo.setAngle(90);  // immediately move to 90°
}

void loop() {
    // Gradual absolute move (self-contained)
    servo.setAnglePeriodically(150, 500);  

    // Gradual relative clockwise move
    servo.moveClockwisePeriodically(10, 200);

    // Gradual relative counterclockwise move
    servo.moveCounterClockwisePeriodically(5, 300);

    // No need to call update() manually
}