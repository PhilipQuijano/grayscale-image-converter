#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "image_processing.h"

// Function to measure execution time
double measureConversionTime(GrayscaleImage* image) {
    clock_t start, end;
    double cpu_time_used;
    
    int total_pixels = image->height * image->width;
    
    start = clock();
    imgCvtGryFltArrEntries(image->float_pixels, image->integer_pixels, total_pixels);
    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

// Function to verify conversion correctness (C implementation for comparison)
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

// Performance testing function
void performanceTest() {
    printf("\n========================================\n");
    printf("      PERFORMANCE TESTING\n");
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
        
        printf("\nTest %d: Image size %dx%d (%d pixels)\n", i+1, height, width, total_pixels);
        
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

// Interactive mode
void interactiveMode() {
    int height, width;
    
    printf("\n========================================\n");
    printf("      INTERACTIVE MODE\n");
    printf("========================================\n");
    
    printf("\nEnter image dimensions:\n");
    printf("Height: ");
    scanf("%d", &height);
    printf("Width: ");
    scanf("%d", &width);
    
    GrayscaleImage* image = createGrayscaleImage(height, width);
    if (image == NULL) {
        printf("Failed to create image\n");
        return;
    }
    
    int choice;
    printf("\nInput method:\n");
    printf("1. Manual input\n");
    printf("2. Random generation\n");
    printf("Choice: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        readFloatPixels(image);
    } else {
        generateRandomFloatPixels(image);
    }
    
    printFloatPixels(image);
    
    printf("\nConverting to integer representation...\n");
    double time_taken = measureConversionTime(image);
    
    printIntegerPixels(image);
    
    printf("\nConversion completed in %.6f seconds\n", time_taken);
    
    verifyCconversion(image, height * width);
    
    freeGrayscaleImage(image);
}

int main() {
    printf("========================================\n");
    printf("   GRAYSCALE IMAGE CONVERTER\n");
    printf("   Float to Integer Conversion\n");
    printf("   Using x86-64 Assembly (SIMD)\n");
    printf("========================================\n");
    
    int mode;
    printf("\nSelect mode:\n");
    printf("1. Interactive mode (manual/random input)\n");
    printf("2. Performance testing mode\n");
    printf("3. Run both\n");
    printf("Choice: ");
    scanf("%d", &mode);
    
    switch(mode) {
        case 1:
            interactiveMode();
            break;
        case 2:
            performanceTest();
            break;
        case 3:
            interactiveMode();
            performanceTest();
            break;
        default:
            printf("Invalid choice\n");
            return 1;
    }
    
    printf("\n========================================\n");
    printf("   Program completed successfully!\n");
    printf("========================================\n");
    
    return 0;
}