#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// assembly function declaration
extern void imgCvtGrayIntToDouble(int height, int width, uint8_t* intPixels, double* floatPixels);

// printing input
void printIntImage(uint8_t* img, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%3d ", img[i * width + j]);
        }
        printf("\n");
    }
}

// printing output
void printFloatImage(double* img, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%.2f ", img[i * width + j]);
        }
        printf("\n");
    }
}

// correctness checking / functional testing
int checkCorrectness(uint8_t* intPixels, double* floatPixels, int size) {
    int correct = 1;
    for (int i = 0; i < size; i++) {
        double expected = intPixels[i] / 255.0;
        double diff = (floatPixels[i] - expected);
        if (diff < 0) {
            diff = -diff;
        }
        if (diff > 0.001) {
            printf("Error at index %d: expected %.4f, got %.4f\n", i, expected, floatPixels[i]);
            correct = 0;
        }
    }
    return correct;
}

int main() {
    // test cases, change if applicable, based on specs :)
    int testSizes[][2] = { {10, 10}, {100, 100}, {1000, 1000} };
    int numTests = 3;
    int numRuns = 30;

    // title printing for formality
    printf("[MP2] x86-to-C interface\n");
    printf("Project Specification: Grayscale Image Conversion\n");
    printf("By: Pineda, Dencel Angelo D. & Punsalan, Emmanuel Gerald G. (LBYARCH-S19A)\n\n");

    // actual conversion
    printf("=== Program Proper ===\n\n");

    // reading dimension inputs
    int exHeight;
    int exWidth;
    printf("Input image dimensions (m n): ");
    if (scanf_s("%d, ", &exHeight) != 1) {
        printf("Error reading height!\n");
        return 1;
    }
    if (scanf_s("%d", &exWidth) != 1) {
        printf("Error reading height!\n");
        return 1;
    }

    // dimension input validation
    if (exHeight <= 0 || exWidth <= 0 || exHeight > 10000 || exWidth > 10000) {
        printf("Invalid dimensions!\n");
        return 1;
    }

    int exSize = exHeight * exWidth; // computing dimension

    // allocating memory for input array
    uint8_t* exampleInt = (uint8_t*)malloc(exSize * sizeof(uint8_t));
    if (!exampleInt) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // reading input pixels
    printf("Input image pixels (a, b, c...): ");
    for (int i = 0; i < exSize; i++) {
        int temp;
        if (scanf_s(" %d%*[,]", &temp) != 1) { // using regex to ignore commas
            printf("Error reading pixel value at index %d!\n", i);
            free(exampleInt); // freeing allocation to avoid performance issues
            return 1;
        }

        // validating input range
        if (temp < 0 || temp > 255) {
            printf("Error: Pixel value must be between 0 and 255!\n");
            free(exampleInt); // freeing allocation to avoid performance issues
            return 1;
        }
        exampleInt[i] = (uint8_t)temp;
    }

    // allocating memory for output array
    double* exampleFloat = (double*)malloc(exSize * sizeof(double));
    if (!exampleFloat) {
        printf("Memory allocation failed!\n");
        free(exampleInt);
        return 1;
    }

    imgCvtGrayIntToDouble(exHeight, exWidth, exampleInt, exampleFloat); // calling asm function

    // printing example run
    printf("\nInput:\n");
    printIntImage(exampleInt, exHeight, exWidth);
    printf("\n");
    printf("Output:\n");
    printFloatImage(exampleFloat, exHeight, exWidth);
    printf("\n");

    // correctness checking / functional testing
    printf("=== Correctness Checking ===\n\n");
    if (checkCorrectness(exampleInt, exampleFloat, exHeight * exWidth)) {
        printf("PASSED!\n\n");
    }
    else {
        printf("FAILED...\n\n");
    }

    free(exampleInt); // free input array
    free(exampleFloat); // free output array

    // performance testing
    printf("=== Performance Testing ===\n");
    srand((unsigned int)time(NULL));

    for (int t = 0; t < numTests; t++) {
        int height = testSizes[t][0];
        int width = testSizes[t][1];
        int size = height * width;

        printf("\nTest Case: %dx%d (%d pixels)\n", height, width, size);

        // allocating memory
        uint8_t* intPixels = (uint8_t*)malloc(size * sizeof(uint8_t));
        double* floatPixels = (double*)malloc(size * sizeof(double));

        // initializing with random values
        for (int i = 0; i < size; i++) {
            intPixels[i] = rand() % 256;
        }
        imgCvtGrayIntToDouble(height, width, intPixels, floatPixels);

        // checking correctness
        if (checkCorrectness(intPixels, floatPixels, size)) {
            printf("Correctness check: PASSED!\n");
        }
        else {
            printf("Correctness check: FAILED...\n");
        }

        // performance metrics
        double totalTime = 0.0;
        clock_t start, end;

        for (int run = 0; run < numRuns; run++) {
            start = clock();
            imgCvtGrayIntToDouble(height, width, intPixels, floatPixels);
            end = clock();
            totalTime += ((double)(end - start)) / CLOCKS_PER_SEC;
        }

        // getting average times
        double avgTime = totalTime / numRuns;
        printf("Average execution time (%d runs): %.6fs\n", numRuns, avgTime);
        printf("Time/pixel: %.9fs\n", avgTime / size);

        // freeing allocation to avoid performance issues
        free(intPixels);
        free(floatPixels);
    }

    return 0;
}