#include "utils.h"
#include "linear.h"

double* solveLinear(double** matrix, double* f, long size) {
    double* y = new double[size];

    double* k_fwd = new double[size];
    double* l_fwd = new double[size];
    k_fwd[0] = 0;
    l_fwd[0] = 0;

    for (long i = 1; i <= size / 2; ++i) {
        double a = i == 1 ? 0 : matrix[i - 1][i - 2];
        double b = matrix[i - 1][i - 1];
        double c = matrix[i - 1][i];
        double k = k_fwd[i - 1];
        double l = l_fwd[i - 1];
        k_fwd[i] = -c / (a * k + b);
        l_fwd[i] = (-a * l + f[i - 1]) / (a * k + b);
    }

    double* k_bwd = new double[size];
    double* l_bwd = new double[size];
    k_bwd[size - 1] = 0;
    l_bwd[size - 1] = 0;
    for (long i = size - 2; i >= size / 2 - 1; --i) {
        double a = matrix[i + 1][i];
        double b = matrix[i + 1][i + 1];
        double c = i == size - 1 ? 0 : matrix[i + 1][i + 2];
        double k = k_bwd[i + 1];
        double l = l_bwd[i + 1];
        k_bwd[i] = -a / (b + c * k);
        l_bwd[i] = (f[i + 1] - c * l) / (b + c * k);
    }

    long m = size / 2;
    double lf = l_fwd[m];
    double lb = l_bwd[m - 1];
    double kf = k_fwd[m];
    double kb = k_bwd[m - 1];
    y[m - 1] = (lf + kf * lb) / (1 - kb * kf);
    y[m] = (lb + kb * lf) / (1 - kb * kf);

    for (long i = m + 1; i < size; ++i) {
        y[i] = k_bwd[i - 1] * y[i - 1] + l_bwd[i - 1];
    }

    for (long i = m - 2; i >= 0; --i) {
        y[i] = k_fwd[i + 1] * y[i + 1] + l_fwd[i + 1];
    }

    return y;
}

double* parallelSolveLinear(double** matrix, double* f, long size) {
    double* y = new double[size];

    double* k_fwd = new double[size];
    double* l_fwd = new double[size];
    k_fwd[0] = 0;
    l_fwd[0] = 0;

    double *k_bwd = new double[size];
    double *l_bwd = new double[size];
    k_bwd[size - 1] = 0;
    l_bwd[size - 1] = 0;

#pragma omp parallel sections
    {
#pragma omp section
        {
            for (long i = 1; i <= size / 2; ++i) {
                double a = i == 1 ? 0 : matrix[i - 1][i - 2];
                double b = matrix[i - 1][i - 1];
                double c = matrix[i - 1][i];
                double k = k_fwd[i - 1];
                double l = l_fwd[i - 1];
                k_fwd[i] = -c / (a * k + b);
                l_fwd[i] = (-a * l + f[i - 1]) / (a * k + b);
            }
        }

#pragma omp section
        {
            for (long i = size - 2; i >= size / 2 - 1; --i) {
                double a = matrix[i + 1][i];
                double b = matrix[i + 1][i + 1];
                double c = i == size - 1 ? 0 : matrix[i + 1][i + 2];
                double k = k_bwd[i + 1];
                double l = l_bwd[i + 1];
                k_bwd[i] = -a / (b + c * k);
                l_bwd[i] = (f[i + 1] - c * l) / (b + c * k);
            }
        }
    }

    long m = size / 2;
    double lf = l_fwd[m];
    double lb = l_bwd[m - 1];
    double kf = k_fwd[m];
    double kb = k_bwd[m - 1];
    y[m - 1] = (lf + kf * lb) / (1 - kb * kf);
    y[m] = (lb + kb * lf) / (1 - kb * kf);

#pragma omp parallel sections
    {
#pragma omp section
        {
            for (long i = m + 1; i < size; ++i) {
                y[i] = k_bwd[i - 1] * y[i - 1] + l_bwd[i - 1];
            }
        }

#pragma omp section
        {
            for (long i = m - 2; i >= 0; --i) {
                y[i] = k_fwd[i + 1] * y[i + 1] + l_fwd[i + 1];
            }
        }
    }

    return y;
}

double testSolve() {
    static double** test_matrix = nullptr;
    if (test_matrix == nullptr) {
        test_matrix = generateDiagonallyDominantMatrix(LINEAR_SIZE);
    }
    static double* test_vector = nullptr;
    if (test_vector == nullptr) {
        test_vector = generateVector(LINEAR_SIZE);
    }
    double* result = solveLinear(test_matrix, test_vector, LINEAR_SIZE);
    double sum = 0;
    for (int i = 0; i < LINEAR_SIZE; i++) {
        sum += result[i];
    }
    return sum;
}

double testParallelSolve() {
    static double** test_matrix_p = nullptr;
    if (test_matrix_p == nullptr) {
        test_matrix_p = generateDiagonallyDominantMatrix(LINEAR_SIZE);
    }
    static double* test_vector_p = nullptr;
    if (test_vector_p == nullptr) {
        test_vector_p = generateVector(LINEAR_SIZE);
    }
    double* result = parallelSolveLinear(test_matrix_p, test_vector_p, LINEAR_SIZE);
    double sum = 0;
    for (int i = 0; i < LINEAR_SIZE; i++) {
        sum += result[i];
    }
    return sum;
}