#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h> // Include OpenMP header

double** allocateMatrix(int N) {
    double** matrix = (double**)malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (double*)malloc(N * sizeof(double));
    }
    return matrix;
}

void freeMatrix(double** matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void initializeMatrices(double** A, double** B, int N) {
    srand(time(NULL));
    double range = 1000 - 10;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = round(((rand() / (double)RAND_MAX) * range + 10) * 1000) / 1000;  // Random value between 10 and 1000
            B[i][j] = round(((rand() / (double)RAND_MAX) * range + 10) * 1000) / 1000;  // Random value between 10 and 1000
        }
    }
}

void multiplyMatrices(double** A, double** B, double** result, int N) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0.0;
            for (int k = 0; k < N; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void printMatrix(double** matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.3lf\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int N = 2;

    double** A = allocateMatrix(N);
    double** B = allocateMatrix(N);
    double** result = allocateMatrix(N);
    initializeMatrices(A, B, N);

    printf("Matrix A:\n");
    printMatrix(A, N);
    printf("Matrix B:\n");
    printMatrix(B, N);

    double start_time = omp_get_wtime();
    multiplyMatrices(A, B, result, N);
    double end_time = omp_get_wtime();

    printf("Resultant matrix:\n");
    printMatrix(result, N);

    printf("Parallel Execution Time: %lf seconds\n", end_time - start_time);

    freeMatrix(A, N);
    freeMatrix(B, N);
    freeMatrix(result, N);

    return 0;
}
