#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	//int arr[10] = {0};
	//int arr[10] = {7, -5};
	int i;
	int j;
	for(i = 0; i < 10; i++){
		if(i == 2) arr[i] = -7;
		if(i == 3) arr[i] = 5;
		printf("%d\n", arr[i]);	
	}
	printf("\n");
	int count = 1;
	int d_arr[3][3] = {};
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++, count++){
			d_arr[i][j] = count;
			printf("%d ", d_arr[i][j]);
		}
		printf("\n");	
	}
	printf("\n");
	int d_arr_1[3][3] = {};
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(j == i) d_arr_1[i][j] = 1;
			printf("%d ", d_arr_1[i][j]);
		}
		printf("\n");	
	}
	printf("\n");	
	int bilet = 123456;
	int a[6] = {0};
	for(i = 0; i < 6; i++){
		a[i] = bilet % 10;
		bilet /= 10; // bilet = bilet / 10;
		printf("%d ", a[i]);
	}
	printf("\n");
	if(a[0] + a[1] + a[2] == a[3] + a[4] + a[5]) printf("Bilet schastlivii\n");
	else printf("Bilet ne schastlivii\n");
	printf("\n");
	int dec = 256;
	int binary[16] = {};
	i = 0;
	while(dec != 0){
		binary[i] = dec % 2;
		dec /= 2;
		if(dec <= 1) binary[i + 1] == dec;
		i++;
	}
	for(i = 15; i >= 0; i--) {
		printf("%d",binary[i]);
		if(i > 0 && i % 4 == 0) printf(" ");
 	}
 	printf("\n");
 	char c = 0;
  	do
  	{
    	printf("i = %c\n", c);
    	c--;
  	} while(c);
	/*
	printf("%d\n", arr[0]);
	printf("%d\n", arr[1]);
	printf("%d\n", arr[2] = -7);
	printf("%d\n", arr[3] = 5);
	printf("%d\n", arr[4]);
	printf("%d\n", arr[5]);
	printf("%d\n", arr[6]);
	printf("%d\n", arr[7]);
	printf("%d\n", arr[8]);
	printf("%d\n", arr[9]);
	*/
	return 0;
}
