#include <iostream>
#include "utils.h"
#include "omp.h"

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

void check() {
    const long num_steps = 10000000;

    int i;
    double x, sum = 0.0;
    double step = 1.0 / (double) num_steps;
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + x;
    }

    printf("check: %f\n", step * sum);
}

int main() {
    double t_start;
    double t_end;
    double avg_time = 0;
    const int STEPS = 1000;

    // Ensure there is no optimizations
    double sum = 0;
    double pi;

    for (int i = 0; i < STEPS; ++i) {
        t_start = omp_get_wtime();
        pi = calcPiParallel();
        t_end = omp_get_wtime();
        avg_time += t_end - t_start;
        sum += pi;
    }
    avg_time /= STEPS;
    sum /= STEPS;
    printf("avg time: %f\n", avg_time);
    printf("pi: %f\n", sum);

    return 0;
}