# Introduction
This module works with a common-cathode RGB LED, which has 4 pins: **Cathode**, **Red**, **Green**, and **Blue**.

It provides simple ways to control the LED:

- **setColor(Color color)**: Sets the LED to a specific color, either predefined or custom.
- **off()**: Turns the LED completely off.
- **toggle()**: Switches the LED on/off while keeping the last color.
- **autoToggle(interval)**: Automatically toggles the LED on and off at a given time interval.

## Predefined Colors
The library includes easy-to-use predefined colors:

- Color::RED()
- Color::GREEN()
- Color::BLUE()
- Color::YELLOW()
- Color::CYAN()
- Color::MAGENTA()
- Color::WHITE()
- Color::OFF()

You can also create custom colors with:

```
Color myColor(128, 64, 255); // RGB values
led.setColor(myColor);
```

This makes controlling RGB LEDs simple and intuitive, letting beginners experiment with colors without worrying about individual PWM values.

# Guidelines
## RGB LED driver example
- Get `RgbLedDriverExample.ino`
- Get `/include/actuators/leds/rgb/RgbLedDriver.h`
- Get `/include/actuators/leds/rgb/Color.h`
- Get `/lib/actuators/leds/rgb/RgbLedDriver.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `RgbLedDriverExample.ino`