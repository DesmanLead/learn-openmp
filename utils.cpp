#include "utils.h"
#include <iostream>
#include <omp.h>

void printMatrix(long size, long** matrix) {
    for (size_t i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%li ", matrix[i][j]);
        }
        printf("\n");
    }
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