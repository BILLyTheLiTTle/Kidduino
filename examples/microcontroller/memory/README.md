# AVR MEMORY MODEL (SIMPLIFIED BUT CORRECT)

## FLASH (PROGRAM MEMORY)
- Non-volatile memory (stores firmware permanently)
- CPU executes program code from here

### .text
- Compiled program instructions (your actual code)

### .rodata
- Unlike a PC, the AVR CPU cannot read data directly from Flash using standard instructions. Therefore, by default, the startup script copies all .rodata from Flash into RAM so the CPU can access it.
- Examples:
  - String Literals (`"hello"`): 
    - Stored in Flash, but copied to RAM at startup.
    - Use the F() macro to keep them exclusively in Flash.
  - Global `const` / `static const` variables: 
    - Stored in Flash, but copied to RAM at startup.
    - Use the PROGMEM attribute to prevent the copy to RAM.
  - Lookup Tables: Precomputed sets of values that will consume both Flash and RAM unless explicitly declared with `PROGMEM`.
  - `constexpr` (C++):
    - For simple scalars (e.g., `constexpr int limit = 10;`), the value is usually "inlined" directly into the machine code instructions. It occupies no dedicated space in RAM or Flash data sections.
    - For arrays or complex objects, they behave like const variables and will be copied to RAM unless `PROGMEM` is used.

### .data load image (IMPORTANT, often hidden)
- Initial values for SRAM .data variables (not the variables themselves, just the value)
  - values of global initialized variables
  - values of static initialized variables
- Exists in Flash only as a startup copy source
- Copied into SRAM at boot

### NOTE
- Flash is not directly writable at runtime like SRAM
- On AVR, Flash is not normally accessed with standard RAM pointers for reading/writing
  - reading is handled transparently by the CPU instruction fetch
  - special mechanisms are used when needed (e.g. `PROGMEM`, `pgm_read_*` on AVR)
- Writing to Flash requires dedicated erase/write sequences (not normal memory writes)

---

## SRAM (NORMAL RAM – 2KB on ATmega328P)

**LOW MEMORY (0x0000)**
|

**.data**
- Global/static variables **with** initial values
- Stored in SRAM at runtime
- Initial values are copied from Flash at startup (from `.data load image`)
- Includes only variables, NOT code or string literals
- After boot, fully writable RAM

**.bss**
- Global/static variables **without** explicit initialization
- Automatically set to 0 at startup
- Stored entirely in SRAM (no Flash copy involved)

**HEAP**
- Dynamic memory (`malloc`, `free`, `new`, `delete`)
- Grows upward in SRAM
- Used rarely in safe embedded design (fragmentation risk)

**FREE RAM**
- Unused SRAM region between heap and stack
- Not a real section, just remaining space

**STACK**
- Function call frames
- Local variables (non-static)
- Interrupt context saving
- Grows downward from top of SRAM
- Very fast but limited space

|
**HIGH MEMORY (end of SRAM)**

---

### POINTER MODEL IN SRAM
- Normal pointers (`char*`, `int*`, `struct*`) point to **SRAM addresses by default**
- Pointer values themselves are stored in SRAM (stack, heap, or globals)

#### IMPORTANT
- SRAM pointers do NOT directly access Flash
- Flash data requires special handling:
  - `F()` macro (AVR Flash strings)
  - `PROGMEM`
  - `pgm_read_*` functions

---

### LINKER SYMBOLS (INTERNAL MEMORY MANAGEMENT)
- `__bss_start`
  - Start of .bss section in SRAM
- `__bss_end`
  - End of .bss
  - Typically used to locate heap start boundary
- `__heap_start`
  - First usable heap address in SRAM
- `__brkval`
  - Current heap boundary (updated by malloc)
  - `0` means heap not yet used

#### IMPORTANT RULES
- Flash stores code + constants (`.text`, `.rodata`, `.data load image`)
- SRAM stores runtime state (`.data`, `.bss`, heap, stack)
- `.data` is copied from Flash into SRAM at startup
- Heap grows upward, stack grows downward (they collide = crash)
- AVR has no memory protection (no MMU → silent corruption possible)
- SRAM is the real “working memory” of the system — Flash is just source + program storage

---
### MMU

### What an MMU is
An MMU is hardware that sits between CPU and memory and does things like:
- translate virtual addresses → physical addresses
- enforce memory protection rules
- isolate processes from each other
- stop illegal memory access

### What it means in practice
With MMU (modern PCs, phones):
- program A cannot touch program B’s memory
- stack overflow gets caught
- segmentation faults happen instead of silent corruption

# Usage of this code
This module works with **AVR SRAM memory profiling**, allowing you to inspect heap usage, stack position, and estimated free/used RAM at runtime.

It relies on internal linker symbols (`__bss_end`, `__brkval`) and a stack probe variable to estimate memory layout.

It provides several simple ways to inspect memory state:
- `getHeapUsed`: Returns the current heap usage in bytes (difference between `_end` of `.bss` and heap end pointer)
- `getFreeRam`: Estimates free RAM by measuring the gap between heap and stack
- `getUsedRamApprox`: Approximates total used RAM as `total RAM - free RAM`
- `getStackPointer`: Returns the current stack pointer address (via local variable address)
- `getHeapEnd`: Returns the current heap end (`__brkval`), useful for debugging heap growth

This is a **diagnostic tool only**. It does not allocate or manage memory — it only observes how memory is being used at runtime.

# Guidelines
## Memory Profiler example
- Get `MemoryProfilerExample.ino`
- Get `/include/microcontroller/memoryMemoryProfiler.h`
- Get `/lib/microcontroller/memoryMemoryProfiler.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `MemoryProfilerExample.ino`