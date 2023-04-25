#include <stdio.h>

static int array[10000][1000];

int main() {
  int sum = 0;
  for (size_t j = 1; j < 1000; j++) {
    for (size_t i = 0; i < 10000; i++) {

      array[i][j] = 2*i+j;
    }
  }
  for (size_t j = 1; j < (1000-1); j++) {
    for (size_t i = 1; i < (10000-1); i++) {

      array[i][j] = array[i-1][j] + 1;
      //printf("%u\n", array[i][j]);

    }
  }
  // for(int i = 0; i < 100000; i++){
  // 	for(int j = 0; j < 1000; j++){
  // 		//sum += array[i][j];
  // 	}
  // }
  printf("%u\n", array[5][999]);
  return sum;
}
