# Introduction
This module works with a **25LC040A SPI EEPROM**, which is basically a tiny digital filing cabinet that forgets nothing even when your Arduino does.

It uses **SPI communication** with a chip-select pin to read and write persistent data.

It provides a few simple ways to interact with the memory:

- `begin`: Initializes SPI and prepares the chip-select pin
- `writeBytes`: Writes raw data to a specific EEPROM address
- `readBytes`: Reads raw data from a specific EEPROM address
- `writeEnable`: Enables write operations (because the chip is paranoid by design)
- `waitWrite`: Blocks execution until the internal write cycle is finished
- `csLow` / `csHigh`: Manually controls chip selection (for when you want to feel in control of something in life)

## How it works (mentally, not emotionally)
- Before writing, the module must explicitly enable writing (`writeEnable`)
- Data is sent over SPI byte-by-byte like it's still 1985
- After writing, the chip internally “thinks” for a moment, so `waitWrite` polls the status register until it’s done
- Reading is simpler: just ask and it obeys

## Key behavior notes
- Writes are not instantaneous — the chip needs time to finish internal storage
- Reads are immediate, because apparently EEPROM is only slow when it feels like it
- Data is raw bytes — no formatting, no mercy, no protection

If you mess up addresses or lengths, it won’t complain. It will just quietly store garbage like a professional liar.

# Guidelines
## EEPROM 25LC040A example
- Get `EEPROM_25LC040A_Example.ino`
- Get `/include/storage/eeprom/EEPROM_25LC040A.h`
- Get `/lib/storage/eeprom/EEPROM_25LC040A.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `EEPROM_25LC040A_Example.ino`