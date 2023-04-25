#include <stdio.h>

static int array[10];

int main() {
  int sum = 0;
  for (size_t i = 0; i < 10; i++) {
    array[i] = i;
  }

  for (int i = 0; i < 10; i += 2) {
    printf("hi %u\n", array[i]);
  }

  return sum;
}
