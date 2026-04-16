#include <float.h>
#include "MemoryProfiler.h"

MemoryProfiler ram(2048);
void printRamStats();
void fillHeapWithRubbish();

void setup() {
    Serial.begin(9600);
}

void loop() {
    printRamStats();
    fillHeapWithRubbish();

    delay(10000);
}

void printRamStats() {
    Serial.print(F("Heap used: "));
    Serial.println(ram.getHeapUsed());

    Serial.print(F("Free RAM: "));
    Serial.println(ram.getFreeRam());

    Serial.print(F("Used RAM approx: "));
    Serial.println(ram.getUsedRamApprox());
}

void fillHeapWithRubbish() {
    void *p = malloc(500);
    ((char*)p)[0] = 1;

    Serial.print(F("ptr: "));
    Serial.println((uint16_t)p);
}