#include <stdio.h>

static int array[1000][999][998];

int main() {
  int sum = 0;
  for (size_t j = 0; j < 999; j++) {
    for (size_t i = 0; i < 1000; i++) {
      for (size_t k = 0; k < 998; k++) {
        array[i][j][k] = array[i][j][k] + 1;
      }
    }
  }
  printf("%u\n", array[10][10][10]);
  return sum;
}
