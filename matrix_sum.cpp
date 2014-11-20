
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