#include <iostream>
#include <cstdlib>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int arr[30][10] = {}, arr_sum[30] = {};
	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 10; j++){
			if(j == 0 || j == 1) arr[i][j] = 1;
			else arr[i][j] = rand() % 2;
			std::cout << arr[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n\nSum table\n\n";
	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 10; j++){
			arr_sum[j] += arr[i][j];
		}
	}
	for(int i = 0; i < 10; i++){
		std::cout << arr_sum[i] << " " ;
	}
	return 0;
}
