// Main C file for image-processing

#include "image-processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double measureConversionTime(GrayscaleImage* image) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            int i = y * image->width + x;
            float float_pixel = image->float_pixels[i];
            image->integer_pixels[i] = imgCvtGrayFloatToInt(float_pixel);
        }
    }
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

void verifyCconversion(const GrayscaleImage* image, int samples) {
    printf("\n=== Verification (C vs Assembly) ===\n");
    printf("Checking first %d pixels:\n", samples);

    int check_count = (samples < image->height * image->width) ? samples : image->height * image->width;
    int mismatches = 0;

    for (int i = 0; i < check_count; i++) {
        float float_val = image->float_pixels[i];
        uint8_t asm_result = image->integer_pixels[i];
        uint8_t c_result = (uint8_t)(float_val * 255.0f + 0.5f); // C calculation with rounding

        if (i < 10) {  // Print first 10
            printf("Pixel %d: Float=%.4f, Assembly=%d, C=%d %s\n",
                i, float_val, asm_result, c_result,
                (asm_result == c_result) ? "[PASS]" : "[FAIL]");
        }

        if (asm_result != c_result) {
            mismatches++;
        }
    }
    printf("\nTotal mismatches: %d out of %d checked\n", mismatches, check_count);
    if (mismatches == 0) {
        printf("[PASS] All checked values match!\n");
    }
}

void performanceTest() {
    printf("\n========================================\n");
    printf("      VERSION 2 PERFORMANCE TESTING\n");
    printf("========================================\n");

    int test_sizes[][2] = {
        {10, 10},       // 100 pixels
        {100, 100},     // 10,000 pixels
        {1000, 1000}    // 1,000,000 pixels
    };

    int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);

    for (int i = 0; i < num_tests; i++) {
        int height = test_sizes[i][0];
        int width = test_sizes[i][1];
        int total_pixels = height * width;

        printf("\nTest %d: Image size %dx%d (%d pixels)\n", i + 1, height, width, total_pixels);

        GrayscaleImage* image = createGrayscaleImage(height, width);
        if (image == NULL) {
            printf("Failed to create image, skipping...\n");
            continue;
        }

        generateRandomFloatPixels(image);

        // Run conversion multiple times and average
        int iterations = (total_pixels < 10000) ? 1000 : (total_pixels < 1000000) ? 100 : 30;
        double total_time = 0.0;

        for (int j = 0; j < iterations; j++) {
            total_time += measureConversionTime(image);
        }

        double avg_time = total_time / iterations;

        printf("Average time over %d iterations: %.6f seconds\n", iterations, avg_time);
        printf("Pixels per second: %.2f\n", total_pixels / avg_time);

        // Verify correctness for first test
        if (i == 0) {
            verifyCconversion(image, 10);
        }

        freeGrayscaleImage(image);
    }
}


int main() {
    int width, height;
    int mode;
    printf("1)Normal Mode, 2)Performance test\n");
    scanf_s("%d", &mode);
    if (mode == 2) {
        performanceTest();
        return 0;
    }

    scanf_s("%d %d", &width, &height);
    GrayscaleImage* newImage = createGrayscaleImage(width, height);

    //random generation only
    generateRandomFloatPixels(newImage);
    printFloatPixels(newImage);

    //Convert Float to Int
    for (int y = 0; y < newImage->height; y++) {
        for (int x = 0; x < newImage->width; x++) {
            int i = y * newImage->width + x;
            float float_pixel = newImage->float_pixels[i];
            newImage->integer_pixels[i] = imgCvtGrayFloatToInt(float_pixel);
        }
    }


    printIntegerPixels(newImage);

    verifyCconversion(newImage, height * width);

    return 0;
}

