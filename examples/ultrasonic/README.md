# Introduction
It works with the **HC-SR04 ultrasonic sensor**, which has 4 pins: *Vcc*, *TRIG*, *ECHO*, and *GND*.

There are three ways to use this sensor with Kidduino:

1. **Ultrasonic sensor blocking reading**
  - Waits for a measurement before continuing.
  - *Simple to use but blocks the whole loop, delaying other code.*
2. **Ultrasonic sensor polling reading**
  - Checks repeatedly if a measurement is ready.
  - *Doesn’t block the loop, but uses some CPU resources constantly.*
3. **Ultrasonic sensor reading with interrupt**
  - Gets notified automatically when a measurement is complete.
  - *Efficient: calculations happen only when a new value arrives.*

This way, beginners can start simple, while advanced users can choose more efficient methods.

# Guidelines
## Ultrasonic sensor blocking reading example
- Get `UltrasonicSensorBlockingExample.ino`
- Get `include/sensors/ultrasonic/UltrasonicSensorBlocking.h`
- Get `/lib/sensors/ultrasonic/UltrasonicSensorBlocking.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `UltrasonicSensorBlockingExample.ino`

## Ultrasonic sensor polling reading example
- Get `UltrasonicSensorPollingExample.ino`
- Get `include/sensors/ultrasonic/UltrasonicSensorPolling.h`
- Get `/lib/sensors/ultrasonic/UltrasonicSensorPolling.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `UltrasonicSensorPollingExample.ino`

## Ultrasonic sensor reading with interrupt example
- Get `UltrasonicSensorInterruptExample.ino`
- Get `include/sensors/ultrasonic/UltrasonicSensorInterrupt.h`
- Get `/lib/sensors/ultrasonic/UltrasonicSensorInterrupt.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `UltrasonicSensorInterruptExample.ino`