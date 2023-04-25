#include <stdio.h>


static int array[1000][10000];

int main(){
	int sum = 0;
	for(size_t i = 0; i < 1000; i++){
		array[i][0] = i;
	}
		for(size_t j = 1; j < 10000; j++){
				for(size_t i = 0; i < 1000; i++){

			array[i][j] = array[i][j-1] + 1;
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
