#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	//Арефметические операции
	int a = 5;
	int b = 7;
	printf("a + b = %d\n", a + b);
	printf("a - b = %d\n", a - b);
	printf("a * b = %d\n", a * b);
	printf("a / b = %f\n", a / b);
	printf("a %% b = %d\n", a % b);
	
	int number = 129346;
	char a1, a2, a3, a4, a5, a6;	
	printf("number = %d\n", number);
	a1 = number % 10; //6
	number = number / 10; //12934
	a2 = number % 10; //4
	number = number / 10; //1293
	a3 = number % 10; //3
	number = number / 10; //129
	a4 = number % 10; //9 
	number = number / 10; //12
	a5 = number % 10; //2
	number = number / 10; //1
	a6 = number;
	printf("%d, %d, %d, %d, %d, %d\n", a6, a5, a4, a3, a2, a1);
	printf("Right part = %d\n", a1 + a2 + a3);
	printf("Left part = %d\n", a4 + a5 + a6);

	printf("a = %d\n", a);
	printf("Increment a++ %d\n", a++);
	printf("a = %d\n", a);
	
	printf("a = %d\n", a = 5);
	printf("Increment ++a %d\n", ++a);
	printf("a = %d\n", a);
	
	printf("b = %d\n", b);
	printf("Decrement b-- %d\n", b--);
	printf("b = %d\n", b);
	
	printf("b = %d\n", b = 7);
	printf("Decrement --b %d\n", --b);
	printf("b = %d\n", b);
	
	//a = 5; a++; a = 5; a = a + 1;
	//a = 5; ++a; a = a + 1; a = 6;
	
	float result = 0;
	result = (float)(a1 + a2) / a3;
	printf("%f\n", result);
	result = (float)(a1 - a2) / (a3 + a4);
	printf("%f\n", result);
	
	//Логические операции
	//>,<,>=,<=,==,!= => 1, 0
	printf("%d", a1 < a2);
	//&& = И, || = ИЛИ, ! = НЕ
	
	printf("%d, %d, %d, %d, %d, %d\n", a6, a5, a4, a3, a2, a1);
	printf("Right part = Left part?\n");
	if(a1 + a2 + a3 == a4 + a5 + a6 + 1){
		printf("Yes\n");
	}
	else{
		printf("No\n");
	}
	char collor;
	printf("Enter collor = ");	
	scanf("%c", &collor);
	if(collor == 'r') printf("RED\n");
	else if(collor == 'g') printf("GREEN\n");
	else if(collor == 'b') printf("BLUE\n");
	else if(collor == 'w') printf("WHITE\n");
	else printf("Not collor\n");
	return 0;
}
