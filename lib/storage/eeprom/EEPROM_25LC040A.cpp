#include "EEPROM_25LC040A.h"

// SPI commands
#define WREN  0x06
#define WRITE 0x02
#define READ  0x03
#define RDSR  0x05

// -------------------- CONSTRUCTOR --------------------

EEPROM_25LC040A::EEPROM_25LC040A(uint8_t csPin) {
    _cs = csPin;
}

// -------------------- INIT --------------------

void EEPROM_25LC040A::begin() {
    pinMode(_cs, OUTPUT);
    csHigh();
    SPI.begin();
}

// -------------------- CHIP SELECT --------------------

void EEPROM_25LC040A::csLow() {
    digitalWrite(_cs, LOW);
}

void EEPROM_25LC040A::csHigh() {
    digitalWrite(_cs, HIGH);
}

// -------------------- WRITE CONTROL --------------------

void EEPROM_25LC040A::writeEnable() {
    csLow();
    SPI.transfer(WREN);
    csHigh();
}

void EEPROM_25LC040A::waitWrite() {
    csLow();
    SPI.transfer(RDSR);

    while (SPI.transfer(0x00) & 0x01) {
        // wait write in progress
    }

    csHigh();
}

// -------------------- LOW LEVEL IO --------------------

void EEPROM_25LC040A::writeBytes(uint16_t addr, const void *data, uint16_t len) {
    writeEnable();

    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    csLow();

    SPI.transfer(WRITE);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr & 0xFF);

    const uint8_t *ptr = (const uint8_t*)data;
    for (uint16_t i = 0; i < len; i++) {
        SPI.transfer(ptr[i]);
    }

    csHigh();

    SPI.endTransaction();

    waitWrite();
}

void EEPROM_25LC040A::readBytes(uint16_t addr, void *data, uint16_t len) {
    csLow();
    SPI.transfer(READ);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr & 0xFF);

    uint8_t *ptr = (uint8_t*)data;
    for (uint16_t i = 0; i < len; i++) {
        ptr[i] = SPI.transfer(0x00);
    }

    csHigh();
}