#include "simpson.h"
#include "math.h"

double simpson(double (*f)(double), double a, double b) {
    // N must be even
    const double N = 2 * SIMPSON_N;
    const double H = (b - a) / N;

    double result = (b - a) / (3 * N);

    double sum1 = 0;
    for (int i = 0; i < N; i += 2) {
        const double X = a + H * i;
        sum1 += f(X);
    }
    sum1 *= 2;

    double sum2 = 0;
    for (int i = 1; i < N; i += 2) {
        const double X = a + H * i;
        sum2 += f(X);
    }
    sum2 *= 4;

    result = result * (sum1 + sum2);
    return result;
}

double simpsonParallel(double (*f)(double), double a, double b) {
    // N must be even
    const double N = 2 * SIMPSON_N;
    const double H = (b - a) / N;

    double result = (b - a) / (3 * N);

    double sum1 = 0;
    double sum2 = 0;
#pragma omp parallel sections
    {
#pragma omp section
        {
            for (int i = 0; i < N; i += 2) {
                const double X = a + H * i;
                sum1 += f(X);
            }
            sum1 *= 2;
        }
#pragma omp section
        {
            for (int i = 1; i < N; i += 2) {
                const double X = a + H * i;
                sum2 += f(X);
            }
            sum2 *= 4;
        }
    }

    result = result * (sum1 + sum2);
    return result;
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