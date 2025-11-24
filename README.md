# Grayscale Image Converter (C + x86-64 Assembly)

## Group Information: GROUP 11
**Members:**
- Namuag
- Quijano

**Section:** S18B 

A C and x86-64 assembly program that converts single-precision float pixel values (0.0 - 1.0) to 8-bit integers (0 - 255) using SIMD instructions.

## Features
- Float-based and integer-based grayscale conversion
- SIMD optimized assembly routines
- Support for various pixel formats

## Requirements
- GCC compiler (MinGW on Windows or WSL)
- NASM assembler
- Make utility

## Performance Analysis
- The program was tested with varying image sizes. The measureConversionTime function was run over 30 iterations for the largest dataset to ensure accuracy.

|   Image Size  |  Total Pixels | Average Time (sec) |
|     10x10     |      100      |      0.000001      |
|    100x100    |     10,000    |      0.000010      |
|   1000x1000   |   1,000,000   |      0.001267      |

### Analysis
The assembly implementation demonstrates high efficiency, processing **1 million pixels in approximately 1.27 milliseconds**.
-   **Throughput:** ~789 Million pixels per second.
-   **Optimization:** By using SIMD registers (`XMM`), the program minimizes memory overhead and performs arithmetic operations directly in the hardware floating-point unit, resulting in near-instantaneous conversion for standard image sizes.
- Please view the **Verification** folder to see screenshot of the test cases and for correctness checking.

## Build Instructions
``````bash
# Navigate to project
cd "PROJECT-DIRECTORY"

# 1. Assemble the x86-64 assembly file
nasm -f win64 src/imgCvtGryFltArrEntries.asm -o src/imgCvtGryFltArrEntries.o

# 2. Compile C object files
gcc -Wall -Wextra -O2 -Isrc -c src/main.c -o src/main.o
gcc -Wall -Wextra -O2 -Isrc -c src/image_processing.c -o src/image_processing.o

# 3. Link and create executable
gcc src/main.o src/image_processing.o src/imgCvtGryFltArrEntries.o -o grayscale_converter.exe

# Run the program
grayscale_converter.exe
``````

## Project Structure
- ``src/`` - Source code (C and assembly)
- ``v2/`` - Alternative implementation programmed by Namuag
- ``docs/`` - Documentation
- ``Verification.`` - Screenshots of test cases and correctness checks
