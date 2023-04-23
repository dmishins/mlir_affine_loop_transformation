#include <stdio.h>

#define N 3000
#define M 3000
#define P 3000

#define TILE_SIZE 1000

int main() {
    static int A[N][M];
    static int B[M][P];
    static int C[N][P];

    // Fill matrices A and B with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = i + j;
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            B[i][j] = i - j;
        }
    }

    // Perform matrix multiplication with tiling
    for (int ii = 0; ii < N; ii += TILE_SIZE) {
        for (int jj = 0; jj < P; jj += TILE_SIZE) {
            for (int kk = 0; kk < M; kk += TILE_SIZE) {
                for (int i = ii; i < ii + TILE_SIZE && i < N; i++) {
                    for (int j = jj; j < jj + TILE_SIZE && j < P; j++) {
                        int sum = 0;
                        for (int k = kk; k < kk + TILE_SIZE && k < M; k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }

    return 0;
}
