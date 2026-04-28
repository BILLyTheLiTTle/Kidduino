# Introduction
This module provides a streamlined interface for serial debugging in Arduino projects. It allows developers to globally manage debug output, enabling or disabling serial communication with a single flag. By using the `F()` macro, it ensures that debug strings are stored in **Flash memory** rather than consuming precious **SRAM**.

The class is designed to act as a wrapper around the standard `Serial` object, providing:
- **Centralized Control**: Toggle all debug output on or off instantly.
- **Visual Organization**: Built-in formatting tools like separators to make logs readable.
- **Memory Efficiency**: Optimized for AVR-based boards to prevent memory crashes during heavy logging.

# Features
- **Conditional Logging**: Automatically checks the `enabled` state before printing, preventing unnecessary serial overhead.
- **Automatic Formattin**g: The `separator()` method provides quick visual breaks in the Serial Monitor without repetitive code.
- **Persistent Configuration**: Store the debugger state within the object to keep logic clean and free of `if (debug) { ... }` blocks throughout your main code.
- **Low-Impact Integration**: Designed to be instantiated as a global object (`dbg`) for easy access across different files and functions.

# How It Works
The `Debugger` class holds a private boolean flag, `_enabled`. When methods like `begin()` or `separator()` are called, the class checks this flag. If `false`, the functions return immediately, effectively silencing the module. This is particularly useful for production code where you want the debug logic to remain in the source but stay inactive during operation.

# Guidelines
## Sleep mode example
- Get `DebuggerExample.ino`
- Get `/include/microcontroller/logging/Debugger.h`
- Get `/lib/microcontroller/logging/Debugger.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `Debugger.ino`