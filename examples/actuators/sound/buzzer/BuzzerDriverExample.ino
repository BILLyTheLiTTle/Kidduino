#include <BuzzerDriver.h>

BuzzerDriver led(11);

void setup() {
    led.begin();
}

void loop() {
    led.autoToggle(500); // every 500ms

}