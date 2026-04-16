# AVR MEMORY MODEL (SIMPLIFIED BUT CORRECT)

## FLASH (PROGRAM MEMORY)
- Non-volatile memory (code storage)
- CPU executes from here
  .text
    -> compiled program instructions

  .rodata
    -> constant data (string literals, const globals)
    -> e.g. "hello", lookup tables

NOTE:
- Flash is NOT directly RAM-accessible as normal pointers
- Special instructions are used to read it

---

## SRAM (NORMAL RAM - 2KB on ATmega328P)

LOW MEMORY (0x0000)
|
|  .data
|    -> global/static variables WITH initial values
|    -> copied from Flash at startup
|
|  .bss
|    -> global/static variables initialized to 0
|    -> cleared at startup
|
|  HEAP
|    -> dynamic memory (malloc/free)
|    -> grows upward
|
|  FREE RAM
|    -> unused SRAM between heap and stack
|
|  STACK
|    -> function calls + local variables
|    -> grows downward
|
HIGH MEMORY (end of SRAM)

---

### POINTER MODEL IN SRAM
- normal pointers live in SRAM:
    char*, int*, struct*
- they point to SRAM addresses by default

IMPORTANT:
- Flash pointers are NOT normal pointers
- they require special handling (e.g. F(), pgm_read)

---

### LINKER SYMBOLS
__bss_start
    -> start of .bss section

__bss_end
    -> end of .data + .bss
    -> start of heap region

__heap_start
    -> first address available for heap allocation

__brkval
    -> current heap end (0 if heap unused)

---

## IMPORTANT RULES
1. FLASH holds code + constants (.text, .rodata)
2. SRAM holds runtime state (.data, .bss, heap, stack)
3. .data is copied from FLASH into SRAM at startup
4. heap and stack share same SRAM space (grow towards each other)
5. stack overflow can corrupt heap and globals
6. memory is not protected (no MMU on AVR)

---

## What an MMU is
An MMU is hardware that sits between CPU and memory and does things like:
- translate virtual addresses → physical addresses
- enforce memory protection rules
- isolate processes from each other
- stop illegal memory access

## What it means in practice
With MMU (modern PCs, phones):
- program A cannot touch program B’s memory
- stack overflow gets caught
- segmentation faults happen instead of silent corruption

# Usage of code
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