#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int trains[5][5][5] = {{{6, 0}, {9, 0}, {12, 0}, {15, 0}, {18, 0}}, 
					{{7, 0}, {11, 11}, {12, 59}, {17, 0}, {23, 19}}, 
					{{8, 0}, {12, 12}, {14, 30}, {20, 25}, {23, 30}}, 
					{{9, 0}, {13, 13}, {16, 17}, {18, 19}, {20, 20}},
					{{10, 0}, {14, 14}, {14, 51}, {21, 21}, {22, 0}}};
	char name_trains[5][12] = {"Lokomotiv", 
							"Lastochka", 
							"Sabsan", 
							"Elektrichka", 
							"Poezd"
						};
	int i, j, hour_prev, hour_next, min_prev, min_next, number_train, interval = 0, max = 0;

	for(i = 0; i < 5; i++){//Количество поездов
		for(j = 0; j < 5 - 1; j++, interval = 0){//Количество интервалов
			hour_prev = trains[i][j][0];
			min_prev = trains[i][j][1];
			hour_next = trains[i][j + 1][0];
			min_next = trains[i][j + 1][1];
			interval = (hour_next - hour_prev) * 100;			
			if(min_next < min_prev) {
				interval -= 100; // interval = interval - 100;
				interval = 60 - (min_prev - min_next);
			}
			else interval = interval + min_next - min_prev;
			if(interval > max) {
				//printf("True\n");
				max = interval;
				number_train = i;
			}	
		}
	}
	
	printf("Max train interval = %d:%d, the name train is ", max / 100, max % 100);
	for(i = 0; i < 12; i++){
		printf("%c", name_trains[number_train][i]);
	}
	

	return 0;
}
