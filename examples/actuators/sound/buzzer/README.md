# Introduction
This module works with a **buzzer**, which has two pins: **Anode** and **Cathode**.

It provides four simple ways to control the LED:

- **on**: Turns the buzzer on
- **off**: Turns the buzzer off
- **toggle**: Switches the buzzer state (on → off, off → on)
- **autoToggle**: Automatically toggles the buzzer on and off at a given time interval

# Guidelines
## Buzzer driver example
- Get `BuzzerDriverExample.ino`
- Get `/include/actuators/sound/buzzer/BuzzerDriver.h`
- Get `/lib/actuators/sound/buzzer/BuzzerDriver.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `BuzzerDriverExample.ino`