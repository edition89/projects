#define CONST_NAME_1 0x10000001U
#define CONST_NAME_2 0x10000001
#define PI 3.1415
#define HELLO_CONST "\"Hello, world\""

#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int r = 5;
	printf("Const value is %f \n", 2 * r * PI);
	printf("Const value is %d \n", CONST_NAME_2);
	printf("Const value is %s \n", HELLO_CONST);
	return 0;
}
