#define N 3000
#define M 3000
#define P 3000

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

    // Perform matrix multiplication
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            int sum = 0;
            for (int k = 0; k < M; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    return 0;
}
