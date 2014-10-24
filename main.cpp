#include <iostream>

using namespace std;

int main() {
    #ifdef _OPENMP
    printf("OpenMP is supported!\n");
    #endif
    printf("posl 11\n");
    #pragma omp parallel
    {
        printf("paralel \n");
    }
    printf("posl 2\n");
    return 0;
}