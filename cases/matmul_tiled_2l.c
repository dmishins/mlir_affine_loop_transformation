#include <stdio.h>

#define N 2400
#define M 2400
#define P 2400

#define TILE_SIZE1 120
#define TILE_SIZE2 40

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

    // Perform matrix multiplication with two levels of tiling
    for (int iii = 0; iii < N; iii += TILE_SIZE1) {
        for (int jjj = 0; jjj < P; jjj += TILE_SIZE1) {
            for (int kkk = 0; kkk < M; kkk += TILE_SIZE1) {
                for (int ii = iii; ii < iii + TILE_SIZE1 && ii < N; ii += TILE_SIZE2) {
                    for (int jj = jjj; jj < jjj + TILE_SIZE1 && jj < P; jj += TILE_SIZE2) {
                        for (int kk = kkk; kk < kkk + TILE_SIZE1 && kk < M; kk += TILE_SIZE2) {
                            for (int i = ii; i < ii + TILE_SIZE2 && i < N; i++) {
                                for (int j = jj; j < jj + TILE_SIZE2 && j < P; j++) {
                                    int sum = 0;
                                    for (int k = kk; k < kk + TILE_SIZE2 && k < M; k++) {
                                        sum += A[i][k] * B[k][j];
                                    }
                                    C[i][j] += sum;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
