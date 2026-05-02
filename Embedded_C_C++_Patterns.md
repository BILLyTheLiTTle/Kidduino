# Arduino C/C++ patterns

# Data Structures

## Structs

### Memory Packing & Alignment Control
In embedded systems, compilers often insert "padding" bytes between members of a struct to align them with the CPU’s word boundaries (usually 4-byte or 8-byte alignment). While this improves CPU performance, it breaks compatibility when mapping data to specific hardware registers or network protocols.
The `__attribute__((packed))` attribute instructs the compiler to **strip all padding**, ensuring the structure occupies the exact minimum number of bytes required by its members.

### Bit-Fields
Bit-fields enable high-density data storage by "packing" multiple variables into a single underlying integer type (like `uint32_t`). Instead of using a whole byte for a boolean flag, you can allocate exactly 1 bit. This is primarily used for **Memory Mapped I/O (MMIO)** and reducing the memory footprint of large arrays of status flags.

## Unions

### Hardware Abstraction Unions
This pattern overlays a bit-field structure onto a raw integer of the same size. By using a `union`, both members share the exact same memory address. This eliminates the need for manual bitwise shifting (`<<`) and masking (`&`) when you want to modify a specific flag, while still allowing you to clear or initialize the entire register in one clock cycle.

## Classes

### Zero-Overhead Hardware Abstraction (Templates)
Templates act as a "blueprint." The compiler generates a specific version of the class only when you use it. In embedded systems, this is primarily used for compile-time configuration. You can pass constants (like a GPIO pin number) or types (like `uint8_t` vs `uint16_t`) as arguments. Because the values are known at compile-time, the compiler can optimize the code as if you had hard-coded the values, often resulting in much smaller and faster machine code.

### Member Const-Correctness (Read-Only Methods)
A `const` member function is a read-only method. Inside these functions, the `this` pointer is treated as a pointer to a constant. This prevents the function from changing any member variables or calling other non-const functions. In embedded systems, this is vital for ensuring that "Getters" or "Status Checks" don't accidentally toggle a GPIO pin or clear a flag that should have remained untouched.
We should avoid using `const` in function if it changes a pin state of Arduino. There is no change in any member, so you are safe to use it but it affects the general environment so we should avoid using it for similar cases.

### Pass-by-Reference (Read/Write)
Pass-by-reference creates an alias for the variable you pass in. Unlike pass-by-value, where a copy is made, any change made to the parameter inside the function happens to the original variable in the calling code. In embedded systems, this is the primary way to "return" multiple values from a single function or to update a shared state (like a buffer or a hardware handle) without the overhead of pointers. By using a pointer for this functionality you need check that ponter is not `null` (`nullptr`), but with the pas-by-reference feature you are sure that the parameter cannot be `null`.

# Memory
See my other note with memory md file as well.

## SRAM

### Typedefs

#### Integer-Pointer Conversion (`uintptr_t`)
While a pointer (`void*`) is for referencing data, a `uintptr_t` is for calculating addresses. It is an integer type that matches the exact width of the CPU's address bus (e.g., 32 bits on an Arduino Uno/STM32 or 64 bits on a modern SoC). Using `uintptr_t` is the only "portable" and safe way to cast a pointer to an integer, as it ensures you won't accidentally truncate the address (lose bits) if you switch to a different processor architecture.

#### Object Size & Capacity (`size_t`)
While `ptrdiff_t` is for the distance between pointers (signed), `size_t` is for the **magnitude** of memory (unsigned). It is guaranteed to be large enough to represent the size of the largest possible object your system can handle. In embedded systems, this is the "go-to" type for array indices, loop counters for buffers, and any function parameter that specifies a memory length (like `memcpy` or `memset`).

#### Pointer Arithmetic Result (`ptrdiff_t`)
When you subtract one pointer from another, the result isn't just a raw number of bytes; it is the **number of elements** between those two addresses. Because the second pointer could be "before" or "after" the first, the result must be able to be negative—hence why `ptrdiff_t` is a signed type. It is defined in `<stddef.h>` and is guaranteed to be large enough to hold the maximum possible distance between any two pointers in memory.

## Pointers

### The Algebraic Method for Pointers
You can solve even the most complex pointer assignments by treating them like **mathematical substitution**. The key is to remember that the **Left-Hand Side (LHS)** of the = is the *container* (where to store), and the **Right-Hand Side (RHS)** is the *value* (what to store).

**Example 1**
```C
uint32_t data[] = {1, 2, 3, 4};
uint32_t *p32 = data;
p32 += 2;
printf("%d", *p32);
```
Steps to solution:<br>
Part 1:<br>
`uint32_t *p32 = &data[0]` -> Always `array` is `&array[0]`<br>
Part 2:<br>
`p32 += 2` -> `p32 = p32 + 2` => (use part 1) => `p32 = &data[0] + 2` -> `p32 = &data[2]`<br>
Solution:<br>
`printf("%d", *p32)` => The `*` does the dereference => Prints `3`.

**Example 2**
```C
uint8_t a = 1;
uint8_t b = 2;
uint8_t c = 3;
uint8_t *data[] = {&a, &b, &c};
uint8_t **p = data;
uint8_t *z = *(p + b);
printf("%d", *z);
// uint8_t **x = p + a;
//printf("%d", **x);
```
Steps to solution:<br>
Part 1:<br>
`uint8_t **p = data;` => `uint8_t **p = &data[0]` => `uint8_t **p = &(&a)` => So `p` contains `&(&a)` since the `**` are in declaration part and not dereferencing it.<br>
Part 2:<br>
`uint8_t *z = *(p + b);` => (use part 1) => `uint8_t *z = *(&data[0] + b);` => (b = 2) => `uint8_t *z = *(&data[0] + 2);` =>
`uint8_t *z = *(&data[2]);` => (`*` eliminates with `&`) => `uint8_t *z = data[2];` => `uint8_t *z = &c;` => `z = &c` and `*z = 3`<br>
Solution:<br>
`printf("%d", *z);` => The `*` does the dereference => Prints `3`.<br>

This way you could solve difficult pointer assignments using you mind! This is no C/C++ but some simple math to solve puzzles, so can you solve the commented code from example 2?

## Flash

### Flash Memory String Macro (`F()`, `__FlashStringHelper`)
By default, any string literal you write—such as `Serial.print("Hello")`—is stored in Flash but copied into the very limited SRAM (Static RAM) as soon as the program starts. Since a typical Arduino Uno has only **2 KB** of SRAM, a few dozen long print statements can easily cause a system crash. The `F()` macro forces the compiler to keep the string in Flash and read it directly from there, byte-by-byte, whenever it is needed.
If you want to use `F()` as parameter in a function, you need to declare this parameter using `__FlashStringHelper`.

### Flash Storage Keyword (`PROGMEM`)
By default, even if a variable is `const` (constant), the Arduino architecture copies it from Flash into SRAM at startup so the CPU can access it quickly. `PROGMEM` overrides this behavior. It is the "manual" version of the `F()` macro, used for larger datasets like lookup tables, font bitmaps, or large arrays of strings that would otherwise instantly overwhelm your RAM. The most common pattern is "The Lookup Table".

### Compile-Time Constants (`constexpr`)
While `const` means "this value won't change after the program starts," `constexpr` is much stronger. It guarantees the value is a **constant expression**. If you use `constexpr`, the compiler does the math once at your desk (during the build), so the microcontroller doesn't have to do it a million times per second in the field. Comparing it with `#define`, `#define` is a dumb text swap; it blindly pastes values before the compiler even starts. `constexpr` is a smart constant; the compiler calculates it with full knowledge of types and scope.

# Speed
In embedded systems, **speed is tied to simplicity**. Standard `math.h` libraries and floating-point operations (like `float` or `double`) are computationally expensive because most small MCUs lack a dedicated Floating Point Unit (FPU), forcing the CPU to emulate math in software. To maximize performance, **avoid extra libraries** and use **Integer Math** or **Fixed-Point Arithmetic** instead. By sticking to native integer types and bitwise operations, you reduce code size (Flash), save memory (RAM), and ensure your logic executes in the fewest clock cycles possible.

# Bitwise Operators

## Bitwise AND Operator (`&`)
In Arduino programming, the `&` operator is used to perform logic at the hardware level. Unlike the logical AND (`&&`), which evaluates true/false statements, the bitwise `&` looks at the binary structure of a variable. <br>
Use `&` whenever you need to **isolate**, **filter**, or **query** specific bits within a variable without changing the rest of the data. It is the "scalpel" of embedded C++:
- **Masking (Clearing Bits)**: The process of clearing specific bits while keeping others
- **Checking a Specific Bit**: Checking the state of a single pin in a hardware register without affecting the rest.
- **Fast Math (Modulo)**: A common trick is using `&` to perform a modulo operation on powers of two. For example, `x & 7` is a lightning-fast way to calculate `x % 8`.

**Truth table**
  
|     A    |    B    | A AND B |
| -------- | ------- | ------- |
|     0    |    0    |    0    |
|     0    |    1    |    0    |
|     1    |    0    |    0    |
|     1    |    1    |    1    |

## Bitwise OR Operator (`|`)
In Arduino programming, the `|` operator is primarily used for "Bit Setting." While the AND (`&`) operator acts as a filter to remove bits, the OR operator acts as a tool to "force" specific bits to become 1 without disturbing the other bits in a variable. This is essential when configuring hardware registers where you want to enable a specific feature (like a Timer or an Interrupt) while leaving the rest of the configuration untouched.<br>
Use `|` whenever you need to **set**, **combine**, or **activate** specific bits within a variable. It is the "switch" that turns bits on without turning others off:
- **Setting Bits (Turn ON)**: If you want to turn on the Nth bit of a register without knowing what the other bits are currently doing.
- **Combining Flags**: Many libraries use bitwise OR to combine multiple options into a single command.
- **Building Values from Bytes**: If you are reading two 8-bit bytes from a sensor and want to combine them into a single 16-bit integer

**Truth table**

|     A    |    B    |  A OR B |
| -------- | ------- | ------- |
|     0    |    0    |    0    |
|     0    |    1    |    1    |
|     1    |    0    |    1    |
|     1    |    1    |    1    |

## Bitwise XOR Operator (`^`)
In Arduino development, the `^` operator is the ultimate "**Toggle Switch**". While OR sets a bit and AND clears a bit, XOR flips a bit to its opposite state. This makes it incredibly useful for blinking LEDs, reversing status flags, or creating simple encryption and checksums. Because XORing a value with itself results in zero, it is also a classic trick for clearing registers or checking if two data sets are identical.<br>
Use `^` whenever you need to **flip**, **toggle**, or **compare differences** in bits. It is the "toggle button" of the bitwise world:
- **Toggling Bits (The Blink Trick)**: If you want to flip a bit from 1 to 0 (or 0 to 1) without checking its current state
- **Simple Checksums (Parity)**: XOR is often used in communication protocols (like NMEA for GPS) to create a "checksum."
- **Swapping Values**: In low-memory environments, you can swap two variables without using a temporary third variable (the "XOR Swap Algorithm")
- **"Is Different" Check**: If you XOR two variables and the result is non-zero, you know at least one bit is different

**Truth table**

|     A    |    B    | A XOR B |
| -------- | ------- | ------- |
|     0    |    0    |    0    |
|     0    |    1    |    1    |
|     1    |    0    |    1    |
|     1    |    1    |    0    |

## Bitwise NOT / One's Complement (`~`)
In Arduino programming, `~` is used for "**Inverting Logic**". It is the binary equivalent of saying "the exact opposite." While the logical NOT (`!`) turns a "true" into a "false," the bitwise `~` transforms the entire binary representation of a value. It is most frequently used in combination with the AND (`&`) operator to clear specific bits (turning them OFF) while leaving all other bits exactly as they were.<br>
Use `~` when you need to **invert a pattern** or **create a "Clear Mask"**. It is the "opposite day" operator for binary data:
- **Clearing Bits (The "Mask-AND-NOT" Trick)**: This is the most common use case in embedded C. If you want to turn OFF a specific bit (e.g., bit 2) without changing anything else, you AND the register with the inverse of that bit.
  1. Target bit: 00000100 (Bit 2)
  2. Inverted mask (~): 11111011
  3. Operation: PORTB &= ~(1 << 2);
  4. Result: Bit 2 is forced to 0, but all other bits are "protected" by the 1s.
- **Inverting Active-Low Logic**: If you are working with hardware that is "Active-Low" (where 0 means ON and 1 means OFF), you can use `~` to flip your program's internal logic to match the physical state of the pins.
- **Creating All-On Patterns**: In unsigned math, `~0` is a quick way to generate a value where every single bit is set to 1, regardless of whether the variable is 8-bit, 16-bit, or 32-bit.

**Truth table**

|     A    |   NOT A |
| -------- | ------- |
|     0    |    1    |
|     1    |    0    |

## Bitwise Shift Right (`>>`)
In Arduino programming, shifting right is the most efficient way to **divide by powers of two** or to **extract specific data** from a larger value. Because it moves bits toward the "Least Significant Bit" (the right side), it effectively reduces the value of the number. For example, shifting a value right by 1 position is mathematically the same as dividing by 2, but it happens much faster than standard division because the CPU simply slides the bits over in a single clock cycle.<br>
Use `>>` whenever you need to **scale down** a value or **discard lower bits** to get to the important data hidden in the higher positions. It is the "slide and divide" tool for binary data:
- **High-Speed Division**: If you need to divide a number by 2, 4, 8, or 16, use `>>`. This is a massive performance boost on 8-bit Arduinos that don't have a hardware division unit.
- **Extracting Bytes from Integers**: If you have a 16-bit int and you only want the "High Byte" (the top 8 bits) to send over I2C or Serial.
- **Reading Serial Data**: When reconstructing a value from multiple bytes received over a sensor bus, you often shift bits into their correct "weight" or position.

## Bitwise Shift Left (`<<`)
In Arduino programming, shifting left is the fastest way to **multiply by powers of two** or to **position a bit** into a specific slot in a register. Because it moves bits toward the "Most Significant Bit" (the left side), it effectively doubles the value of the number for every position shifted. It is the primary tool used for "Bit Construction," where you take a single bit and move it to the exact location needed to turn on a specific hardware feature.<br>
Use `<<` whenever you need to **scale up** a value or **place a bit** into a specific position (like a pin number). It is the "slide and multiply" tool for binary data:
- **High-Speed Multiplication**: If you need to multiply by 2, 4, 8, etc., `<<` is significantly faster than the `*` operator on a microcontroller.
- **Creating Bit Masks**: Instead of memorizing that the 5th bit is "32", you can write (`1 << 5`). This is much more readable and tells other developers exactly which bit you are targeting.
- **Packing Bytes into Integers**: If you receive two 8-bit bytes and want to turn them into one 16-bit `int`.

# Keywords
## The Read-Only Qualifier (`const`)
On an Arduino, `const` primarily ensures code safety. Unlike a standard PC, simply adding `const` to a global variable does not automatically move it to Flash memory; the AVR architecture still copies `const` variables into SRAM at startup so the CPU can access them using standard instructions. To actually save RAM, you must combine `const` with the `PROGMEM` keyword. However, `const` remains essential for preventing accidental changes to pin numbers or settings and allowing the compiler to perform "inlining" optimizations that make your code run faster.

## The Anti-Optimization Qualifier (`volatile`)
In Arduino programming, the compiler tries to be "smart" by caching variable values in CPU registers to save time. However, if a variable is changed by something outside the normal flow of your `loop()`—such as a **Hardware Interrupt (ISR)** or a hardware register (like a Timer)—the compiler might not realize the value has changed. It will keep using the old "cached" version, causing your code to miss updates. Marking a variable as `volatile` forces the CPU to physically check the SRAM every single time the variable is mentioned, ensuring you always have the most current data.

## The External Reference (`extern`)
In multi-file Arduino projects, each `.cpp` or `.ino` file is compiled in isolation. If File A needs to use a variable defined in File B, you must use `extern` in File A to prevent an "undefined variable" error. The most efficient way to manage this is the **Header Pattern**: you **define** the variable once in a `.cpp` file (creating the memory) and **declare** it as `extern` in a `.h` file. Any file that includes that header can then read and write to that single, shared piece of memory.

## The Persistent & Private Scope (`static`)
In Arduino programming, `static` is most commonly used inside a function to create a variable that "remembers" its value even after the function finishes. Unlike a regular local variable (which is destroyed and recreated every time the function runs), a `static` local variable is initialized only once and stays in memory for the duration of the program. When used outside of a function (at the file level), `static` acts as a privacy shield, ensuring that other files in your project cannot access that specific variable or function, even if they use `extern`.
