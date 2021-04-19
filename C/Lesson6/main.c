#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void main(int argc, char *argv[]) {
	printf("%d\n", plus_one(5));
	printf("%d\n", sum(5, 7));
	simple(997);
	quadratic_equation(1, 2, 3);
}

int plus_one(int a){
	return a + 1;
}

int sum(int a, int b){
	return a + b;
}

void simple(int a){
	int i;
	for(i = 2; i <= a; i++){
		if(a % i == 0 && a != i){
			printf("It's number not simple\n");
			break;
		}
		if(i == a) printf("It's number simple\n");
	}
}

void quadratic_equation(int a, int b, int c){
	float D = 0;
	if(a == 0) printf("It's not quadratic equation\n");
	D = b * b - 4 * a * c;
	if(D > 0){
		float x1 = (-b + sqrt(D))/ (2 * a);
		float x2 = (-b - sqrt(D))/ (2 * a);
		printf("x1 = %f\nx2 = %f\n", x1, x2);
	}
	else if(D == 0){
		float x = -b / (2 * a);		
		printf("x = %f\n", x);
	}
	else printf("D < 0, korni veshestvenniie");
}
