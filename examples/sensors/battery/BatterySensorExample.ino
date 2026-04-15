#include "Battery.h"

Battery battery(A1, 10.0, 15.0);

void setup() {
    Serial.begin(9600);

    battery.begin();
}

void loop() {
    float v = battery.readFilteredVoltage();
    int p = battery.readPercent();

    Serial.print("Battery: ");
    Serial.print(p);
    Serial.print("% (");
    Serial.print(v);
    Serial.println("V)");

    delay(1000);
}