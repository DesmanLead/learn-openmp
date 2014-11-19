#include <iostream>
#include "math.h"
#include "simpson.h"
#include "utils.h"

using namespace std;

void matrixSum() {
    const long size = 8;

    long A[size][size] = {
            { 1, 1, 1, 2, 1, 1, 1, 2 },
            { 1, 1, 2, 1, 1, 1, 1, 2 },
            { 1, 2, 1, 1, 1, 1, 1, 2 },
            { 2, 1, 1, 1, 1, 1, 1, 2 },
            { 1, 1, 1, 2, 1, 1, 1, 2 },
            { 1, 1, 2, 1, 1, 1, 1, 2 },
            { 1, 2, 1, 1, 1, 1, 1, 2 },
            { 2, 1, 1, 1, 1, 1, 1, 2 }
    };

    long B[size][size] = {
            { -1,  1, 1,  1, -1,  1, 1,  1 },
            {  1,  1, 1,  1,  1,  1, 1,  1 },
            { -1,  1, 1,  1, -1,  1, 1,  1 },
            {  1, -1, 1, -1,  1, -1, 1, -1 },
            { -1,  1, 1,  1, -1,  1, 1,  1 },
            {  1,  1, 1,  1,  1,  1, 1,  1 },
            { -1,  1, 1,  1, -1,  1, 1,  1 },
            {  1, -1, 1, -1,  1, -1, 1, -1 }
    };

    double** result = new double*[size];
    for (int i = 0; i < size; i++) {
        result[i] = new double[size];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] * A[i][j] + B[i][j] * B[i][j];
        }
    }

    for (int i = 0; i < size; i++) {
        delete [] result[i];
    }
    delete [] result;
}

void matrixSumParallel() {
    const long size = 8;

    long A[size][size] = {
            { 1, 1, 1, 2, 1, 1, 1, 2 },
            { 1, 1, 2, 1, 1, 1, 1, 2 },
            { 1, 2, 1, 1, 1, 1, 1, 2 },
            { 2, 1, 1, 1, 1, 1, 1, 2 },
            { 1, 1, 1, 2, 1, 1, 1, 2 },
            { 1, 1, 2, 1, 1, 1, 1, 2 },
            { 1, 2, 1, 1, 1, 1, 1, 2 },
            { 2, 1, 1, 1, 1, 1, 1, 2 }
    };

    long B[size][size] = {
            { -1,  1, 1,  1, -1,  1, 1,  1 },
            {  1,  1, 1,  1,  1,  1, 1,  1 },
            { -1,  1, 1,  1, -1,  1, 1,  1 },
            {  1, -1, 1, -1,  1, -1, 1, -1 },
            { -1,  1, 1,  1, -1,  1, 1,  1 },
            {  1,  1, 1,  1,  1,  1, 1,  1 },
            { -1,  1, 1,  1, -1,  1, 1,  1 },
            {  1, -1, 1, -1,  1, -1, 1, -1 }
    };

    long** result = new long*[size];
    for (int i = 0; i < size; i++) {
        result[i] = new long[size];
    }

#pragma omp parallel sections
    {
#pragma omp section
            {
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < i; j++) {
                        result[i][j] = A[i][j] * A[i][j] + B[i][j] * B[i][j];
                    }
                }
            }
#pragma omp section
            {
                for (int i = 0; i < size; i++) {
                    for (int j = i; j < size; j++) {
                        result[i][j] = A[i][j] * A[i][j] + B[i][j] * B[i][j];
                    }
                }
            }
    }

    for (int i = 0; i < size; i++) {
        delete [] result[i];
    }
    delete [] result;
}

double calcPiParallel() {
    const long n = 10000000;

    int i;
    double x, sum = 0.0;
    double h = 1.0 / (double) n;
#pragma omp parallel default(none) private(i,x) shared(h) reduction(+:sum)
    {
        #pragma omp for schedule (auto)
        for (i = 0; i < n; ++i) {
//            printf("i: %d, thread: %d\n", i, omp_get_thread_num());
            x = (i + 0.5) * h;
            sum = sum + 4.0 / (1.0 + x * x);
        }
    }
    return h * sum;
}

void calcPi() {
    const long num_steps = 10000000;

    int i;
    double x, pi, sum = 0.0;
    double step = 1.0 / (double) num_steps;
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    printf("%1.8f\n", pi);
}

double func(double x) {
    return x * sin(x) * cos(x);
}

double testSimpson() {
    return simpson(&func, 0, 1);
}

double testParallelSimpson() {
    return simpsonParallel(&func, 0, 1);
}

int main() {
    double** matrix = generateDiagonallyDominantMatrix(4);
    printMatrix(4, matrix);
    return 0;
}