# Introduction
It works with **standard hobby servo motors**, connected to a single digital PWM pin.

There are three ways to control this servo with the ServoMotorDriver class:

1. Immediate moves
  - Functions: `setAngle()`, `moveClockwise()`, `moveCounterClockwise()`
  - Moves the servo to the target angle instantly.
  - *Simple and straightforward, but no gradual motion.*
2. Gradual periodic moves
  - Functions: `setAnglePeriodically()`, `moveClockwisePeriodically()`, `moveCounterClockwisePeriodically()`
  - Moves the servo gradually, step by step, over time.
  - *Non-blocking: other code can run while the servo moves.*
3. Relative moves
  - Move clockwise or counterclockwise by a specific number of degrees, either immediately or gradually.
  - *Useful for incremental adjustments without calculating absolute angles.*

This setup lets beginners move the servo instantly, while advanced users can implement smooth, timed movements without blocking the main loop.

# Guidelines
## Servo motor example
- Get `ServoMotorDriverExample.ino`
- Get `/include/actuators/servo/ServoMotorDriver.h`
- Get `/lib/sensors/actuators/servo/ServoMotorDriver.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `ServoMotorDriverExample.ino`