It works with the **HC-SR04 ultrasonic sensor**, which has 4 pins: *Vcc*, *TRIG*, *ECHO*, and *GND*.

There are three ways to use this sensor with Kidduino:

1. **UltrasonicSensorBlocking**
  - Waits for a measurement before continuing.
  - *Simple to use but blocks the whole loop, delaying other code.*
2. **UltrasonicSensorPolling**
  - Checks repeatedly if a measurement is ready.
  - *Doesn’t block the loop, but uses some CPU resources constantly.*
3. UltrasonicSensorInterrupt
  - Gets notified automatically when a measurement is complete.
  - *Efficient: calculations happen only when a new value arrives.*

This way, beginners can start simple, while advanced users can choose more efficient methods.