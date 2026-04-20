#pragma once

#include <Arduino.h>
#include <SPI.h>

class EEPROM_25LC040A {
public:
    EEPROM_25LC040A(uint8_t csPin);

    void begin();

    void readBytes(uint16_t addr, void *data, uint16_t len);
    void writeBytes(uint16_t addr, const void *data, uint16_t len);

    void writeByte(uint16_t addr, uint8_t data);
    uint8_t readByte(uint16_t addr);

    void factoryReset();

private:
    uint8_t _cs;

    void csLow();
    void csHigh();

    void writeEnable();
    void waitWrite();
};