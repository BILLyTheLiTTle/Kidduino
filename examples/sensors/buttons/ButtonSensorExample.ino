#include "ButtonSensor.h"

ButtonSensor btn(2);

void setup() {
    Serial.begin(9600);
}

void loop() {
    btn.update();

    ButtonEvent e = btn.getEvent();

    if (e != BUTTON_NONE) {

        switch (e) {
            case BUTTON_CLICK:
                Serial.println("CLICK");
                break;

            case BUTTON_DOUBLE_CLICK:
                Serial.println("DOUBLE CLICK");
                break;

            case BUTTON_LONG_CLICK:
                Serial.println("LONG CLICK");
                break;

            default:
                break;
        }

        btn.clearEvent();
    }
}