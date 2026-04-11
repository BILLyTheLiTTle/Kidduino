**DO NOT TRY THIS MODULE, NEEDS TESTING!!!**

# Introduction
This library works with LM393-based speed sensors (IR or reflective modules) connected to an Arduino board.

It measures rotational speed using pulse detection and converts it to:
- RPM (rotations per minute)
- RPS (rotations per second)
- Linear speed (m/s and km/h)

# How It Works
The LM393 module outputs a digital pulse each time a hole, slot, or reflective mark passes in front of the sensor.

- Each pulse = partial rotation
- Multiple pulses = full rotation
- Speed is calculated over time using pulse frequency

The library uses:
- **Interrupts** for accurate pulse counting
- **Time-based sampling** for stable speed calculation
- **Software debounce** to filter noise

# Configuration Parameters
When creating the sensor object, you must define:
- `pin`
  - Arduino interrupt-capable pin connected to sensor output
- `pulsesPerRevolution`
  - Number of pulses for one full rotation (e.g. number of holes in disk)
- `wheelCircumference`
  - Wheel perimeter in meters (used for linear speed)
- `debounceMicros` (optional)
  - Minimum time between pulses to filter noise (default: 500 µs)

# Measurement Model
The library calculates speed using a time window approach:
- Counts pulses over a time interval
- Converts pulses → rotations
- Converts rotations → RPM and speed

This avoids blocking delays and allows continuous operation.

# Available Methods
- `begin()`
  - Initializes the sensor and attaches interrupt
- `update()`
  - Updates internal speed calculations
  - Must be called regularly in loop()
- `getRPM()`
  - Returns rotations per minute
- `getRPS()`
  - Returns rotations per second
- `getSpeedMps()`
  - Returns linear speed in meters per second
- `getSpeedKmph()`
  - Returns linear speed in km/h
- `getPulseCount()`
  - Returns total detected pulses

# Usage Patterns
## Continuous Monitoring
- Call `update()` in the main loop
- Read speed values periodically
- *Non-blocking and suitable for real-time systems*

## Low-Speed Accuracy
- Use longer time intervals between readings (e.g. 500 ms)
- Improves stability when pulses are sparse

## High-Speed Tracking
- Ensure debounce is not too large
- Prevents missing valid pulses at high RPM

# Noise Handling
LM393 sensors can produce unstable signals due to:
- Light variations
- Surface reflectivity
- Mechanical vibration

This library includes:
- Software debounce using `micros()`

For best results:
- Adjust the module’s potentiometer
- Tune `debounceMicros` based on your setup

# Limitations
- Designed for **single sensor instance**
- Requires interrupt-capable pins
- Accuracy depends on correct configuration:
  - Wrong pulses per revolution → incorrect RPM
  - Wrong circumference → incorrect speed

# Typical Applications
- Wheel speed measurement (robots, carts, RC vehicles)
- Motor RPM tracking
- Distance estimation
- Educational projects involving motion and sensors

This library provides a simple interface for beginners while maintaining accurate, non-blocking measurements suitable for more advanced embedded applications.

# Guidelines
## LM393 speed sensor example
- Get `LM393SpeedSensorExample.ino`
- Get `/include/sensors/speed/LM393SpeedSensor.h`
- Get `/lib/sensors/speed/LM393SpeedSensor.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `LM393SpeedSensorExample.ino`