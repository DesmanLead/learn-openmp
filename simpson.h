#ifndef SIMPSON_H
#define SIMPSON_H

#define SIMPSON_N 1000000

double simpson(double (*f)(double), double a, double b);

double simpsonParallel(double (*f)(double), double a, double b);

#endif