#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a;		
	a = rand() % 5; //Генерация рандома
	//printf("Enter number 1..5\n");
	//scanf("%d", &a);
	switch(a){ //Функция Switc case
		case 1: printf("This is 1\n");
				break;
		case 2: printf("This is 2\n");
				break;
		case 3: printf("This is 3\n");
				break;
		case 4: printf("This is 4\n");
				break;
		case 5: printf("This is 5\n");
				break;
		default: printf("default\n");
				break;
	}
	if(a == 1) printf("This is 1\n");
	else if(a == 2) printf("This is 2\n");
	else if(a == 3) printf("This is 3\n");
	else if(a == 4) printf("This is 4\n");
	else if(a == 5) printf("This is 5\n");
	else printf("default\n");
	int x = 3, y = 7, z = 0;
	//Тернарный оператор
	if(x > y){
		z = x;
	}
	else {
		z = y;
	}
	printf("%d\n", z);
	z = 0;
	z = (x > y) ? x : y; // x > y = True -> z = x, x > y = False -> z = y
	printf("%d\n", z);
	
	int ball = 21, color = 0;
	char ball_color;
	if(ball > 20){
		if(color == 1){
			printf("white");
		}
		else printf("black");
	}
	else {
		printf("red");
	}
	ball_color = (ball > 20) ? (color == 1) ? 'w' : 'b' : 'r';
	printf("%c\n", ball_color);
	return 0;
}
