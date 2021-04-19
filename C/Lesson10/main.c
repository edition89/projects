#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]){
	int i;
	if(argc == 1){
		printf("Print command.\n");
		return 0;
	}
	for(i = 0; i < argc; i++) {
		if(argv[1][i] == 'h') {
			printf("Command name: -a, -r and -b.\n");
			return 0;
		}
	}
	for(i = 0; i < argc; i++) {
		if(argv[1][i] == 'a') {
			printf("1, 2, 3, 4, 5, 6, 7, 8, 9, 10.\n");
			return 0;
		}
		else if(argv[1][i] == 'r') {
			printf("I, II, III, IV, V, VI, VII, VIII, IX, X\n");
			return 0;
		}
		else if(argv[1][i] == 'b') {
			printf("0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001, 1010\n");
			return 0;
		}
	}
	printf("Command not found!");
	return 0;
}
