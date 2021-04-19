#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int c, a = 26, b = 7;
	c = (float)a / b;
	printf("%d\n", c);
	printf("%f\n", (float)a / b);
	char cc = 50;
	printf("%c\n", cc);
	cc = cc - 5;
	printf("%c\n", cc);
	return 0;
}
