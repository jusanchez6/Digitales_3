# SHA256 RP2350 Hardware Library

### Overview

This repository contains a hardware abstraction library for the SHA-256 cryptographic module of the **RP2350**. The library provides access to the memory-mapped registers of the SHA-256 hardware accelerator, allowing for fast and efficient hashing operations directly on the hardware.

### Features
- Full control over the **SHA-256 Control and Status Register (CSR)**.
- Provides **start**, **write data ready**, **sum valid**, and **error flags** through easy-to-use macros.
- Support for **DMA configuration** with multiple size options (8, 16, and 32-bit).
- Optional **byte swapping** for different endianness requirements.
- Atomic XOR, SET, and CLEAR operations on registers.
- Access to **checksum result registers** SUM0-SUM7, allowing direct retrieval of the hash.

### Files

- **SHA256.h**: Header file that declares data types, constants, and macros for controlling the RP2350 SHA-256 hardware module.

### Usage

1. **Include the library** in your project:

    ```c
    #include "SHA256.h"
    ```

2. **Initialize and start the SHA-256 hardware module**:

    ```c
    setSHA256_START; // Start hashing operation
    ```

3. **Write your data** to the SHA-256 Write Data register:

    ```c
    rSHA256_WDATA = my_data;
    ```

4. **Check the status**:

    ```c
    if (bSHA256_WDATA_RDY) {
        // Data is ready to be processed
    }
    ```

5. **Retrieve the checksum** once the operation is complete:

    ```c
    uint32_t result = rSHA256_SUM0; // Get part of the hash
    ```

### API Documentation

#### Control and Status Register (CSR)

- **CSR Flags**:
    - `bSHA256_START`: Start a new checksum operation.
    - `bSHA256_WDATA_RDY`: Indicates if data is ready to write.
    - `bSHA256_SUM_VLD`: Check if the checksum is valid.
    - `bSHA256_ERR_WDATA_NOT_RDY`: Error flag if data was written when not ready.
    
- **Macros**:
    - `setSHA256_START`: Set the start bit to begin hashing.
    - `clrSHA256_DMA_SIZE`: Clear the DMA size configuration.
    - `xorSHA256_BSWAP`: XOR the byte swap configuration.

#### Checksum Result Registers

- **SUM0-SUM7**:
    - Access the 256-bit hash result through the `rSHA256_SUMX` macros:
      - `rSHA256_SUM0`: First 32-bit word of the checksum.
      - `rSHA256_SUM1` to `rSHA256_SUM7`: Subsequent parts of the 256-bit hash.

### Example

```c
#include "SHA256.h"

int main() {
    // Start the SHA-256 module
    setSHA256_START;
    
    // Write some data to be hashed
    rSHA256_WDATA = 0xDEADBEEF;
    
    // Wait for the data to be processed
    while (!bSHA256_WDATA_RDY);
    
    // Retrieve the checksum
    uint32_t hash = rSHA256_SUM0;
    
    return 0;
}
