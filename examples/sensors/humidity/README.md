# Introduction
It works with a soil moisture sensor, which has 2–4 pins depending on the type: **VCC**, **GND**, **Analog output**, and optional **Digital output**.

There are three ways to use this sensor with Kidduino:

1. Analog reading
  - Reads the moisture level as a number from 0–1023.
  - *Simple to use but gives raw values—you have to decide what counts as “wet” or “dry".*
2. Averaged reading
  - Takes multiple analog readings and calculates the average.
  - *Smoother and more stable than a single reading, especially if the soil is patchy.*
3. Digital threshold check
  - Returns `true` if soil is wet, `false` if dry, based on a set threshold.
  - *Easy for beginners: you don’t have to interpret numbers, just get wet/dry status.*

This way, beginners can start simple, while advanced users can choose more accurate or reliable methods.

# Guidelines
## Soil moisture sensor example
- Get `SoilMoistureSensorExample.ino`
- Get `/include/sensors/humidity/SoilMoistureSensor.h`
- Get `/lib/sensors/humidity/SoilMoistureSensor.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `SoilMoistureSensorExample.ino`