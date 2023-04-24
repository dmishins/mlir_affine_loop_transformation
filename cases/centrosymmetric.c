#include <stdio.h>

#define M 20
#define N 10

static int array[M][N];

int main() {
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      array[i][j] = i + j;
    }
  }
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      array[j][i] = array[M - j - 1][N - i - 1];
    }
  }
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      printf("%u ", array[i][j]);
    }
    printf("\n");
  }
}
