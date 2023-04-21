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
  // for(size_t i = 1; i < 100000; i++){
  // 	for(size_t j = 0; j < 1000; j++){
  // 		array[i][j] = array[i-1][j];
  // 	}
  // }
  // for(int i = 0; i < 100000; i++){
  // 	for(int j = 0; j < 1000; j++){
  // 		//sum += array[i][j];
  // 	}
  // }
  // printf("%u\n", array[5]);
  return sum;
}
