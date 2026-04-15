# Introduction
This module works with a **battery voltage divider system**, which uses two resistors to safely scale down a higher battery voltage so it can be measured by an Arduino analog input pin.

It allows safe monitoring of battery packs.

---

# Hardware Setup

The voltage divider is built using two resistors:
- **R1 (Top resistor)**: Connected between the battery positive terminal (+) and the analog input pin
- **R2 (Bottom resistor)**: Connected between the analog input pin and ground (GND)

### Resistor values for this example
- **R1 = 10kΩ**
- **R2 = 15kΩ**

These values scale 8.4V down to approximately:
- ~5.0V max at the Arduino analog pin (safe operating range)


# Guidelines
## Battery sensor example
- Get `BatterySensorExample.ino`
- Get `/include/sensors/battery/Battery.h`
- Get `/lib/sensors/battery/Battery.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `BatterySensorExample.ino`