#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <stdint.h>
#include <stdlib.h>

// Grayscale image data
typedef struct {
    int height;
    int width;
    float* float_pixels;      // Float-based representation (0.0 to 1.0)
    uint8_t* integer_pixels;  // Integer-based representation (0 to 255)
} GrayscaleImage;

// C function: MEMORY ALLOCATION
GrayscaleImage* createGrayscaleImage(int height, int width);

// C function: FREEING ALLOCATED MEMORY
void freeGrayscaleImage(GrayscaleImage* image);

// C function: FLOAT PIXEL VALUES PRINTING
void printFloatPixels(const GrayscaleImage* image);

// C function: INTEGER PIXEL VALUES PRINTING
void printIntegerPixels(const GrayscaleImage* image);

// C function: FLOAT PIXEL VALUES READING
void readFloatPixels(GrayscaleImage* image);

// C function: RANDOM FLOAT PIXEL VALUES GENERATION
void generateRandomFloatPixels(GrayscaleImage* image);

// ASSEMBLY FUNCTION : FLOAT TO INTEGER CONVERSION
extern uint8_t imgCvtGrayFloatToInt(float float_pixels);
#endif