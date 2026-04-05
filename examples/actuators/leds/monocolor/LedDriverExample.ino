#include <LedDriver.h>

LedDriver led(13); // built-in LED on most boards

void setup() {
    led.begin();
}

void loop() {
    led.autoToggle(500); // blink every 500ms

}