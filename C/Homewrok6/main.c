#include <stdio.h>
#include <stdlib.h>

// run this program using the console pauser or add your own getch, system("pause") or input loop /

int main(int argc, char *argv[]) {
	int N = 10,i,sum,mul;
	int A[10] = {0};
	for (i = 0; i < N; i++){
		A[i] = rand() % 201 - 101;
		printf("%d ", A[i]);
	}
	return 0;
}
