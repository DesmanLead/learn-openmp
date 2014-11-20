#include "utils.h"
#include <iostream>
#include <omp.h>

void printMatrix(long size, double** matrix) {
    for (size_t i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printVector(long size, double* vector) {
    for (size_t i = 0; i < size; ++i) {
        printf("%f ", vector[i]);
    }
    printf("\n");
}

void measure(double (*f)()) {
    double t_start;
    double t_end;
    double avg_time = 0;

    // Ensure there is no optimizations
    double sum = 0;
    double result;

    for (int i = 0; i < MEASURE_STEPS; ++i) {
        t_start = omp_get_wtime();
        result = f();
        t_end = omp_get_wtime();
        avg_time += t_end - t_start;
        sum += result;
    }
    avg_time /= MEASURE_STEPS;
    sum /= MEASURE_STEPS;
    printf("avg time: %f\n", avg_time);
    printf("avg value: %f\n", sum);
}

double** generateDiagonallyDominantMatrix(long size) {
    if (size == 0) {
        return nullptr;
    }

    double** matrix = new double*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new double[size];
    }

    if (size == 1) {
        matrix[0][0] = 1;
        return matrix;
    }

    matrix[0][0] = 10;
    matrix[0][1] = 5;
    for (int i = 1; i < size - 1; ++i) {
        matrix[i][i - 1] = (double) i / 3.0;
        matrix[i][i]     = (double) i;
        matrix[i][i + 1] = (double) i / 3.0;
    }
    matrix[size - 1][size - 2] = 5;
    matrix[size - 1][size - 1] = 10;

    return matrix;
}

double* generateVector(long size) {
    if (size == 0) {
        return nullptr;
    }

    double* vector = new double[size];

    for (long i = 0; i < size; ++i) {
        vector[i] = 15.0;
    }

    return vector;
}
