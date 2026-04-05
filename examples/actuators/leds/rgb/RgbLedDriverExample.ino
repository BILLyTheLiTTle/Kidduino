#include <RgbLedDriver.h>
#include <Color.h>

RgbLedDriver led(9, 10, 11);

void setup() {
    led.begin();
}

void loop() {
    led.setColor(Color::RED());
    delay(1000);

    led.setColor(Color::GREEN());
    delay(1000);

    led.setColor(Color::BLUE());
    delay(1000);

    Color orange = Color(255, 128, 0);
    led.setColor(orange);
    delay(1000);

    // Auto toggle example
    led.autoToggle(500); // toggles every 500ms non-blocking
}