# Introduction
This module provides a robust interface for managing **Atmega328P Power-Down sleep modes** using a hardware interrupt pin. It is designed to maximize battery life by disabling peripherals like the ADC and handling the synchronization between hardware states and software logic.

It provides a safe way to transition the system between two states:
- **Active**: The system is awake and processing code.
- **Sleep**: The system is in deep power-down mode, waiting for a hardware trigger.

# Features
- **Deep Sleep Management**: Automates the `avr/sleep.h` workflow (set mode, disable ADC, enable/disable sleep).
- **Interrupt Safety**: Specifically handles the "LOW-level interrupt freeze" issue by attaching interrupts only right before sleeping.
- **Hardware Abstraction**: Manages the static context required for C++ ISRs (Interrupt Service Routines).
- **ADC Power Saving**: Automatically saves and restores the ADC state to save power during sleep.

# How It Works
The module uses a **Level-triggered (LOW)** interrupt to wake the CPU. Unlike edge-triggered interrupts (RISING/FALLING), the LOW level does not require an active system clock, making it the most reliable way to wake up from the deepest `SLEEP_MODE_PWR_DOWN`.

# Basic Usage
- **begin**: Initializes the pin as `INPUT_PULLUP` and performs an initial state check.
- **update**: Syncs the internal `SystemState` with the physical pin voltage.
- **enable**: Prepares the hardware and puts the MCU into deep sleep. The function blocks until the pin is pulled LOW.
- **getState**: Returns whether the system is currently `ACTIVE` or in `SLEEP` logic.

# Guidelines
## Sleep mode example
- Get `SleepModeExample.ino`
- Get `/include/microcontroller/power/*.h`
- Get `/lib/microcontroller/power/SleepMode.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `SleepModeExample.ino`