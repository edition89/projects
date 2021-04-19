#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	float a = 5, b = 5, c = 1, D;
	
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
	return 0;
}
