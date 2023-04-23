#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000
#define M 10000
#define P 10000

void matmul(double **A, double **B, double **C, int n, int m, int p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            C[i][j] = 0;
            for (int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

double **allocate_matrix(int n, int m) {
    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(m * sizeof(double));
    }
    return matrix;
}

void free_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void fill_matrix(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

int main() {
    double **A = allocate_matrix(N, M);
    double **B = allocate_matrix(M, P);
    double **C = allocate_matrix(N, P);

    srand(time(NULL));
    fill_matrix(A, N, M);
    fill_matrix(B, M, P);

    matmul(A, B, C, N, M, P);

    free_matrix(A, N);
    free_matrix(B, M);
    free_matrix(C, N);

    return 0;
}
