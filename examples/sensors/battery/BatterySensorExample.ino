#include "Battery.h"

Battery battery(A1, 10.0, 15.0);

void setup() {
    Serial.begin(9600);

    battery.begin();
}

void loop() {
    uint16_t voltage = battery.readVoltage();

    uint8_t voltage_int = voltage / 1000; 
    uint8_t voltage_frac = (voltage % 1000) / 10; // convert fraction to centiVolts to avoid 3 digits and show only 2 digits

    uint8_t p = battery.readPercent();

    Serial.print(F(" Battery: "));
    Serial.print(p);
    Serial.print(F("% ("));
    Serial.print(voltage_int);
    Serial.print(F("."));
    if (voltage_frac < 10)  Serial.print(F("0"));
    Serial.print(voltage_frac);
    Serial.println(F("V)"));

    if(voltage <= Battery::LOWER_BOUND_VOLTAGE) {
        Serial.println(F("  Batteries need to recharge!"));
    }

    delay(1000);
}