#include "EEPROM_25LC040A.h"

EEPROM_25LC040A eeprom(10);

const char* writeData = "Hello World";

void setup() {
    Serial.begin(9600);

    eeprom.begin();

    // write string including null terminator
    eeprom.writeBytes(0x0000, writeData, strlen(writeData) + 1);
}

void loop() {

    char readBuffer[32];

    Serial.print("Before read: ");
    Serial.println(readBuffer);   // uninitialized garbage (important to show difference)

    eeprom.readBytes(0x0000, readBuffer, strlen("Hello World") + 1);

    Serial.print("After read: ");
    Serial.println(readBuffer);

    delay(10000);
}