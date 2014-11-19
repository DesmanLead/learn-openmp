#ifndef UTILS_H
#define UTILS_H

void printMatrix(long size, double** matrix);

#define MEASURE_STEPS 100

void measure(double (*f)());

double** generateDiagonallyDominantMatrix(long size);

#endif