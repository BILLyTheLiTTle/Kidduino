/*
Pins:
1 (CS) -> D10
2 (SO) -> D12
3 (WP) -> 5V
4 (VSS) -> GND
5 (SI) -> D11
6 (SCK) -> D13
7 (HOLD) -> 5V
8 (VCC) -> 5V

Almost identical with this wiring (https://wolles-elektronikkiste.de/wp-content/uploads/2022/03/Wiring_25LC512_Arduino_Nano.png)
apart from WP(D9), HOLD(5V) pins.
*/

#pragma once

#include <Arduino.h>
#include <SPI.h>

class EEPROM_25LC040A {
public:
    EEPROM_25LC040A(uint8_t csPin);

    void begin();

    void readBytes(uint16_t addr, void *data, uint16_t len);
    void writeBytes(uint16_t addr, const void *data, uint16_t len);

private:
    uint8_t _cs;

    void csLow();
    void csHigh();

    void writeEnable();
    void waitWrite();
};