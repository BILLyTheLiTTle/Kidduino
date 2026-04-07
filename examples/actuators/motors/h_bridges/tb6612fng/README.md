**DO NOT TRY THIS MODULE, NEEDS TESTING!!!**

# Introduction
This library works with **standard DC motors** connected via an TB6612FNG H-bridge to your Arduino board.

## System vs User Settings
- System Settings (`NORMAL`, `SAFE`)
  - High-level rules enforced by the system.
  - `SAFE` ensures smooth acceleration and deceleration to protect gears and electronics.
  - `NORMAL` allows full-speed operation, respecting user preferences.
- User Settings (`INSTANT`, `SMOOTH`)
  - Low-level driver preferences for PWM ramping.
  - `INSTANT` jumps immediately to the requested speed.
  - `SMOOTH` ramps speed gradually.
  - `SystemSettings` may override `UserSettings` (e.g., `SAFE` forces `SMOOTH`).

## Control Methods
- Forward / Backward
  - Functions: `forward(speed)`, `backward(speed)`
  - Moves the motor at the requested speed (0–100%).
  - `SAFE` mode smooths the ramp for gentle acceleration.
  - Speed below 10% triggers braking for hill-hold / gear protection.
- Brake / Coast
  - `brake()` – actively stops the motor.
  - `coast()` – lets the motor spin freely without applying power.
  - Useful for teaching concepts like inertia and controlled stopping.
- Dual Motor Support
  - `TB6612FNGFull` handles two motors independently with the same interface.
  - Each motor can move forward/backward, brake, or coast individually or together.

## Usage Scenarios
- Immediate moves
  - `forward(100)` or `backward(50)`
  - Moves motors instantly to the requested speed.
  - *Simple, direct control, but can stress gears if used carelessly.*
- Gradual ramped moves
  - Set `UserSettings::SMOOTH` or `SystemSettings::SAFE`
  - Motors accelerate and decelerate smoothly.
  - *Non-blocking: allows other code to run while motors ramp up/down.*
- Incremental or safe demos
  - Speed 0–10% triggers braking instead of moving.
  - Useful for beginner-friendly demonstrations, teaching SAFE operation.

This setup lets beginners control DC motors simply, while giving advanced users full access to ramp control, SAFE modes, and dual motor operation without blocking the main loop.

# Guidelines
## TB6612FNG Half H-Bridge example
- Get `TB6612FNGHalfExample.ino`
- Get `/include/actuators/h_bridges/tb6612fng/TB6612FNGHalf.h`
- Get `/lib/sensors/actuators/h_bridges/tb6612fng/TB6612FNGHalf.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `TB6612FNGHalfExample.ino`

## TB6612FNG Full H-Bridge example
- Get `TB6612FNGFullExample.ino`
- Get `/include/actuators/h_bridges/tb6612fng/TB6612FNGFull.h`
- Get `/lib/sensors/actuators/h_bridges/tb6612fng/TB6612FNGFull.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `TB6612FNGFullExample.ino`