#include <stdio.h>
#include <stdlib.h>
int b = 10;
//printf("%d\n", b);
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void binary(unsigned short a){
	printf("%d\n", b);
	b--;
	int i = 0;
	char c[16] = {};
	/*
	for(i = 0; i < 16; i++){
		c[i] = a % 2;
		a /= 2;
	}
	*/
	RUN:
	c[i] = a % 2;
	a /= 2;
	i++;
	if(i < 16) goto RUN;
	for(i = 15; i >= 0; i--) {
		printf("%d", c[i]);
		if(i % 4 == 0) printf(" ");
	}
	printf("\n");
	printf("\n");
}
int main(int argc, char *argv[]) {
	printf("%d\n", b);
	int aa = 5;
	binary(aa);
	i++;
	binary(1024 + 512 + 128);
	binary(1792 >> 3);
	binary(1792 << 4);
	printf("1792: >> 3 = %d, << 4 = %d\n\n", 1792 >> 3, 1792 << 4);
	binary(7623);
	printf("+\n");
	binary(15978);
	printf("________________________\n");
	binary(7623 + 15978);
	binary(15978);
	printf("-\n");
	binary(7623);
	printf("________________________\n");
	binary(15978 - 7623);
	binary(7623);
	printf("&\n");
	binary(15978);
	printf("________________________\n");
	binary(7623 & 15978);
	binary(7623);
	printf("|\n");
	binary(15978);
	printf("________________________\n");
	binary(7623 | 15978);
	binary(65535);
	printf("^\n");
	binary(15978);
	printf("________________________\n");
	binary(65535 ^ 15978);
	printf("~\n");
	binary(15978);
	printf("________________________\n");
	binary(~ 15978);
	return 0;
}
