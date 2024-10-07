# RP2350 ADC Library

## Overview

This library provides an interface for the Analog-to-Digital Converter (ADC) module on the RP2350 board. It allows users to control the ADC's operation, read conversion results, and manage FIFO (First In, First Out) functionalities.

## Features

- **Control and Status Register (CS)**: Enables and configures the ADC operations.
- **Result Register (RST)**: Retrieves the latest ADC conversion result.
- **FIFO Control and Status Register (FCS)**: Manages FIFO operations, including error handling and DMA request enabling.
- **FIFO Register**: Contains the conversion results in a FIFO format.
- **Clock Divider Register (DIV)**: Configures the clock divider for ADC operations.
- **Interrupt Registers**: Manages and monitors interrupts related to ADC operations.

## Structure Definitions

### Control and Status Register (`__ADC_CS_t`)

This register controls the ADC functionality and provides status information.

- `ADC_EN`: Enable/disable the ADC.
- `ADCTS_EN`: Enable/disable the power temperature sensor.
- `ADC_START_ONCE`: Start a single conversion.
- `ADC_START_MANY`: Start multiple conversions.
- `ADC_Ready`: Indicates if the ADC is ready.
- `ADC_ERR`: Indicates an ADC error.
- `ADC_STICKY`: Indicates a sticky error.

### Result Register (`__ADC_RESULT_t`)

This register holds the result of the most recent ADC conversion.

- `ADC_RESULT`: The conversion result.

### FIFO Control and Status Register (`__ADC_FCS_REGISTER_t`)

Manages FIFO settings and status.

- `FCS_EN`: Enable/disable FIFO.
- `FCS_ERR`: Indicates a FIFO error.
- `FCS_EMPTY`: Indicates if the FIFO is empty.
- `FCS_FULL`: Indicates if the FIFO is full.

### FIFO Register (`__ADC_FIFO_REGISTER_t`)

Contains the conversion results stored in the FIFO.

- `FIFO_DATA`: The data from the FIFO.
- `FIFO_ERR`: Indicates if there was a FIFO error.

### Clock Divider Register (`__ADC_DIV_REGISTER_t`)

Configures the clock division settings.

- `DIV_FRAC`: Fractional part of the divider.
- `DIV_INT`: Integer part of the divider.

### Interrupt Registers

- **INTR**: Raw interrupt status.
- **INTE**: Interrupt enable.
- **INTF**: Force an interrupt.
- **INTS**: Interrupt status after masking and forcing.

## Usage

To use the ADC library in your project:

1. Include the header file:
    ```c
    #include "adc.h"
    ```

2. Initialize the ADC by enabling it:
    ```c
    rADC_CS = kADC_CS_ADC_ENABLE;
    ```

3. Start a conversion:
    ```c
    rADC_CS |= kADC_CS_ADC_START_ONCE;
    ```

4. Read the conversion result:
    ```c
    uint32_t result = bADC_RESULT;
    ```

5. Handle FIFO as needed:
    ```c
    if (bADC_FCS_EMPTY) {
        // Handle empty FIFO
    }
    ```

## Examples

### Example: Basic ADC Initialization and Read

```c
#include "adc.h"

int main() {
    // Enable ADC
    rADC_CS = kADC_CS_ADC_ENABLE;

    // Start a single conversion
    rADC_CS |= kADC_CS_ADC_START_ONCE;

    // Wait for conversion to complete
    while (!bADC_CS_ADC_Ready);

    // Read the result
    uint32_t adcValue = bADC_RESULT;

    // Do something with adcValue
    return 0;
}
