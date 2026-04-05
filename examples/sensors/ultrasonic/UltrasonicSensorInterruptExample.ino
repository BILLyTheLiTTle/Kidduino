#include <UltrasonicSensorInterrupt.h>

UltrasonicSensorInterrupt sensor(4, 3);

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  sensor.update();
  Serial.println(sensor.read());
}