# Introduction
This module works with a **single-color LED**, which has two pins: **Anode** and **Cathode**.

It provides four simple ways to control the LED:

- **on**: Turns the LED on
- **off**: Turns the LED off
- **toggle**: Switches the LED state (on → off, off → on)
- **autoToggle**: Automatically toggles the LED on and off at a given time interval

# Guidelines
## LED driver example
- Get `LedDriverExample.ino`
- Get `/include/actuators/leds/monocolor/LedDriver.h`
- Get `/lib/actuators/leds/monocolor/LedDriver.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `LedDriverExample.ino`