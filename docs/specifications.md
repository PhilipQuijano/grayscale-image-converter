# Grayscale Image Converter - Project Specifications

## Overview
A grayscale image is internally represented as a 2-dimensional array. Size is defined by the number of pixels in a row (width), and number of pixels in a column (height). Each cell represents the pixel value. Pixel values in grayscale are represented as white, black, and shades of gray using different numerical data type representation depending on the library used.

## Image Representations

### Image 1: Float-based representation
- **Size**: 0.5, 0.45, 0.33
- **Values**: 
  - 0.5, 0.45, 0.33
  - 0.45, 0.40, 0.30
  - 0.85, 0.95, 0.15, 0.13

### Image 2: Integer-based representation  
Some libraries represent values in 8-bit unsigned integer (0 for black, 255 for white, 64 lighter gray, 191 darker gray, and all other gray values in between).

- **Values**:
  - 64, 95, 154, 64
  - 140, 154, 191, 84
  - 224, 242, 38, 64

## Conversion Methods

To enable using different image processing libraries (for different formats), conversion from one format to the other has to be done. Perform Mapping from single precision float based grayscale to unsigned 8-bit based integer representations. Each pixel is calculated using ratio and proportion equation:

**Formula**: `(pixel_float / 1.0) = (pixel_integer / 255.0)`

Where:
- `pixel_float` is the float based pixel value
- `pixel_integer` is the integer based pixel value

## Task

Implement a program that converts the grayscale image representations from float-based to integer-based using C and x86 assembly language.

### Requirements

1. **Functional Scalar SIMD Registers**
   - Required to use functional scalar SIMD registers
   - Required to use functional SIMD floating-point instructions

2. **Input/Output**
   - Input: height, width, single float pixel values
   - Output: integer pixel values

3. **Example Input**

    3 4
    0.5 0.25 0.45 0.33
    0.5 0.40 0.75 0.33
    0.85 0.95 0.5 0.33

4. **Example Output**

    64, 95, 154, 64
    140, 154, 191, 84
    224, 242, 38, 64

5. **Notes**
   - C is responsible for collecting the inputs, allocating memory space for the images, and printing the outputs
   - Assembly function is responsible for converting the data type from the input pixel float pixels into the output int pixels
   - Perform Mapping from single precision float based grayscale to unsigned 8-bit based integer representation
   - Each pixel is calculated using only ratio and proportion equation

## Deliverables

### Program Components

1. **C Program with initialization and correct call/passing parameters to C and x86-64 program**
   - Points: 25

2. **Correct output x86-64**
   - Points: 40

3. **Performance result**
   - Points: 20

4. **Videos**
   - Points: 10

5. **GitHub Repository with Instructions**
   - Points: 5 (see -10 instruction)


- **Important**: 
- Time the data function call for input image sizes with "height = 10" and "width = 10", and then "height = 100" and "width = 100", and "height = 1000" and "width = 1000". If input size is impossible, you may reduce it to the point your machine can support. You may use a random number generator to generate pixel values for the input.
- For the data, you may initialize each pixel with the same or different random values
- You will still need to check the correctness of your output
- Output of files needed to run your project: (source code, C_x86-64, and all other required files) for others to test and execute your program