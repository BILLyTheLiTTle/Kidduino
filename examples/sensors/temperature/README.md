# Thermistor Module

## Introduction
This module works with a **thermistor temperature sensor**, which has two terminals. It is used to measure temperature by reading changes in resistance.

It provides a simple interface to read temperature and handle sensor status:
- **readTemperatureC()**: Returns the measured temperature in Celsius
- **readTemperatureK()**: Returns the measured temperature in Kelvin
- **getStatus()**: Returns the current sensor status (`OK`, `SHORT_TO_GND`, `SHORT_TO_VCC`, `INVALID`)

---

## Wiring

The thermistor is connected in a voltage divider configuration:
- One side of the thermistor → **GND**
- Other side → **Analog pin + series resistor**
- Series resistor → **VCC (5V or 3.3V depending on system)**

---

## Configuration Parameters

The module is initialized with the following parameters:
- **analogPin**: ADC pin used to read the voltage
- **seriesResistor**: Fixed resistor value in the voltage divider (The actual resisotr used in wiring)
- **nominalResistance**: Thermistor resistance at nominal temperature (usually 10kΩ)
- **nominalTemperature**: Reference temperature (usually 25°C)
- **beta**: Beta coefficient of the thermistor (e.g. 3950)

---

## Sensor Status

The module can report sensor health:
- `OK`: Sensor working normally
- `SHORT_TO_GND`: Sensor shorted to ground
- `SHORT_TO_VCC`: Sensor shorted to VCC
- `INVALID`: Invalid ADC reading or disconnected sensor

---

## Notes
- Accuracy depends on thermistor tolerance and resistor precision
- Best results achieved with proper calibration and stable wiring
- Beta model is used for temperature calculation (no Steinhart-Hart complexity)

# Guidelines
## Thermistor sensor example
- Get `TemperatureSensorExample.ino`
- Get `/include/sensors/temperature/*.h`
- Get `/lib/sensors/temperature/Thermistor.cpp`
- Store them in the same folder
- Open the Arduino IDE and run the `TemperatureSensorExample.ino`