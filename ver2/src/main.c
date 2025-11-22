// Main C file for image-processing

#include "image-processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int width, height;
	scanf_s("%d %d", &width, &height);
	GrayscaleImage* newImage = createGrayscaleImage(width, height);
	
	//TODO: Ask for user input or generate random pixels
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


	return 0;
}
