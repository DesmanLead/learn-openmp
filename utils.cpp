#include "utils.h"
#include <iostream>

void printMatrix(long size, long** matrix) {
    for (size_t i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%li ", matrix[i][j]);
        }
        printf("\n");
    }
}