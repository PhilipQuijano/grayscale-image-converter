#include "image_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// MEMORY ALLOCATION FOR GREYSCALE IMAGE
GrayscaleImage* createGrayscaleImage(int height, int width) {
    if (height <= 0 || width <= 0) {
        fprintf(stderr, "Error: Invalid image dimensions\n");
        return NULL;
    }

    GrayscaleImage* image = (GrayscaleImage*)malloc(sizeof(GrayscaleImage));
    if (image == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for image structure\n");
        return NULL;
    }

    image->height = height;
    image->width = width;

    int total_pixels = height * width;

    // FLOAT PIXELS MEMORY ALLOCATION
    image->float_pixels = (float*)malloc(total_pixels * sizeof(float));
    if (image->float_pixels == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for float pixels\n");
        free(image);
        return NULL;
    }

    // INTEGER PIXELS MEMORY ALLOCATION
    image->integer_pixels = (uint8_t*)malloc(total_pixels * sizeof(uint8_t));
    if (image->integer_pixels == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for integer pixels\n");
        free(image->float_pixels);
        free(image);
        return NULL;
    }

    return image;
}

void freeGrayscaleImage(GrayscaleImage* image) {
    if (image != NULL) {
        if (image->float_pixels != NULL) {
            free(image->float_pixels);
        }
        if (image->integer_pixels != NULL) {
            free(image->integer_pixels);
        }
        free(image);
    }
}

// PRINTING
void printFloatPixels(const GrayscaleImage* image) {
    if (image == NULL) {
        fprintf(stderr, "Error: NULL image pointer\n");
        return;
    }

    printf("\nFloat-based pixel values:\n");
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            printf("%.2f ", image->float_pixels[i * image->width + j]);
        }
        printf("\n");
    }
}

void printIntegerPixels(const GrayscaleImage* image) {
    if (image == NULL) {
        fprintf(stderr, "Error: NULL image pointer\n");
        return;
    }

    printf("\nInteger-based pixel values:\n");
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            printf("%3d ", image->integer_pixels[i * image->width + j]);
        }
        printf("\n");
    }
}

void readFloatPixels(GrayscaleImage* image) {
    if (image == NULL) {
        fprintf(stderr, "Error: NULL image pointer\n");
        return;
    }

    printf("Enter %d float pixel values (0.0 to 1.0):\n", image->height * image->width);
    for (int i = 0; i < image->height * image->width; i++) {
        scanf("%f", &image->float_pixels[i]);
        
        if (image->float_pixels[i] < 0.0f || image->float_pixels[i] > 1.0f) {
            fprintf(stderr, "Warning: Pixel value %.2f out of range [0.0, 1.0], clamping...\n", 
                    image->float_pixels[i]);
            if (image->float_pixels[i] < 0.0f) image->float_pixels[i] = 0.0f;
            if (image->float_pixels[i] > 1.0f) image->float_pixels[i] = 1.0f;
        }
    }
}

void generateRandomFloatPixels(GrayscaleImage* image) {
    if (image == NULL) {
        fprintf(stderr, "Error: NULL image pointer\n");
        return;
    }

    // random number generator
    srand((unsigned int)time(NULL));

    for (int i = 0; i < image->height * image->width; i++) {
        image->float_pixels[i] = (float)rand() / (float)RAND_MAX;
    }

    printf("Generated %d random float pixel values\n", image->height * image->width);
}