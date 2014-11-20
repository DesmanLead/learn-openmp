#ifndef UTILS_H
#define UTILS_H

void printMatrix(long size, double** matrix);
void printVector(long size, double* vector);

#define MEASURE_STEPS 100
void measure(double (*f)());

double** generateDiagonallyDominantMatrix(long size);
double* generateVector(long size);

#endif