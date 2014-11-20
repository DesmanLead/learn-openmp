#ifndef LINEAR_H
#define LINEAR_H

double* solveLinear(double** matrix, double* f, long size);
double* parallelSolveLinear(double** matrix, double* f, long size);

#define LINEAR_SIZE 20000
double testSolve();
double testParallelSolve();

#endif