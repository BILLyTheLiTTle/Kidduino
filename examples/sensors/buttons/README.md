# Introduction
This module handles a **push button input** properly.

Buttons are noisy and timing-sensitive. This module takes care of:
- debouncing
- click detection (click, long click, double click)
- timing logic

This is not “just a button”.

It’s a small input system that:
- filters noise
- understands timing
- produces clean events

Use it once, and stop rewriting button logic forever.

---

# Supported Events

The module detects three types of user interaction:

- **Click**  
  A short press and release

- **Double Click**  
  Two presses within a configurable time window

- **Long Click**  
  A press held longer than a defined duration

---

# Behavior

- **Debounce is handled internally** (no false triggers from bouncing). You, still, need the capacitor in hardware level for hardware debouncing as well.
- **Non-blocking** (no `delay()` used)
- **Event priority is enforced:**
  1. Long click
  2. Double click
  3. Single click

- **Single click is delayed slightly**  
  This is required to confirm that a second click does not follow

---

# Configuration

The constructor allows tuning:

```cpp
Button btn(pin, debounceMs, doubleClickMs, longClickMs);
```

- `debounceMs` → filters mechanical noise (typical: 10–20 ms)
- `doubleClickMs` → max interval between clicks (typical: ~250 ms)
- `longClickMs` → press duration for long click (typical: 500–800 ms)

# Guidelines
## Button driver example
- Get `ButtonSensorExample.ino`
- Get `/include/sensors/buttons/ButtonSensor.h`
- Get `/lib/sensors/buttons/ButtonSensor.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `ButtonSensorExample.ino`