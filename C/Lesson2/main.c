#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	short n16; //-32 768 ... 32767
	unsigned short un16, un16_1, un16_2; //0 ... 65535
	int n32, n32_1;
	unsigned int un32, un32_1;
	long n32l;
	unsigned long un32l;
	long long n32ll;
	unsigned long long un32ll;
	float f;
	double d;
	char c1, c2, c3, c4;
	
	n16 = 123;
	un16 = 777;
	un16_1 = 65535-55+1;
	un16_2 = -55;
	printf("n16 = %d\n", n16);
	printf("un16 = %d\n", un16);
	printf("un16_1 = %d\n", un16_1);
	printf("un16_2 = %d\n", un16_2);
	
	n32 = -123;
	un32 = 777;
	un32_1 = 4294967295 + 1;
	n32_1 = 2147483647 + 1;
	printf("n32 = %d\n", n32);
	printf("un32 = %d\n", un32);
	printf("un32_1 = %d\n", un32_1);
	printf("n32_1 = %d\n", n32_1);
	
	c1 = 'H';
	c2 = 'A';
	c3 = 'N';
	c4 = 'D';
	printf("%c%c%c%c\n", c1, c2, c3, c4);
	
	printf("It's type of short: %d. It's type of int: %i.\n", n16, n32);
	printf("It's type of int: %u. n32 = - 123\n", n32);
	
	printf("It's type of unsigned short: %u. n16 = 777\n", un16);
	printf("HEX 0x%X\n", un16);
	printf("OCT 0%o\n", un16);
	
	f = 124.54321f;
	d = 922337203.11115d;
	
	printf("It's type of float: %fe. f = 124.54\n", f);
	printf("It's type of double: %lfE. d = 9223372036854775808.0\n", d);
	
	printf("It's type of String: %s.\n", "Hello wrold");
	printf("It's %% .\n");
	
	printf("It's type of float: %.2fe. f = 124.54321\n", f);
	printf("It's type of double: %.4lfE. d = 922337203.11115\n", d);
	
	char C1 = 65;
	char C2 = 0x41;
	char C3 = 'A';
	
	printf("C1 = %c, C2 = %d, C3 = %X", C1, C2, C3);
	
	return 0;

}
