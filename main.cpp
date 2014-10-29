#include <iostream>
#include "utils.h"

using namespace std;

void matrixSum() {
    const long size = 4;

    long A[size][size] = {
            { 1, 1, 1, 2 },
            { 1, 1, 2, 1 },
            { 1, 2, 1, 1 },
            { 2, 1, 1, 1 }
    };

    long B[size][size] = {
            { -1,  1, 1,  1 },
            {  1,  1, 1,  1 },
            { -1,  1, 1,  1 },
            {  1, -1, 1, -1 }
    };

    long** result = new long*[size];
    for (int i = 0; i < size; i++) {
        result[i] = new long[size];
    }

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < i; j++) {
                        result[i][j] = A[i][j] + B[i][j];
                    }
                }
            }
#pragma omp section
            {
                for (int i = 0; i < size; i++) {
                    for (int j = i; j < size; j++) {
                        result[i][j] = A[i][j] + B[i][j];
                    }
                }
            }
        }
    }

    printMatrix(size, result);
}

void calcPi() {
    const long num_steps = 1000;

    int i;
    double x, pi, sum = 0.0;
    double step = 1.0 / (double) num_steps;
#pragma omp parallel for private(x) reduction(+:sum)
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    printf("%f", pi);
}

int main() {
    matrixSum();
    return 0;
}