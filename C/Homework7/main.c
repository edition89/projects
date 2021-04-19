#include <stdio.h>
#include <stdlib.h>

// run this program using the console pauser or add your own getch, system("pause") or input loop /

int main(int argc, char *argv[]) {
	char _text[] = "ded,oko,privet,topot,ToPOT,Mem,loL,KeK,cheburek,asdfgfdsa";
	int start = 0, end = 0, i = 0, j = 0, flag = 0, length = 0;
	while (_text[length] != '\0') length++;
	while (_text[i] != '\0'){
		if (_text[i] == ',' || length - 2 == i){			
			end = i;
			if(length - 2 == i) end += 2;
			for(i = start; i < end; i++){							
				flag = 0;
				if (_text[i] != _text[start + end - 1 - i]){
					if(_text[i] > _text[start + end - 1 - i]){
						if(_text[i] - 32 != _text[start + end - 1 - i]){
							flag = 1;
							break;
						}
					}
					if(_text[i] < _text[start + end - 1 - i]){
						if(_text[i] != _text[start + end - 1 - i] - 32){
							flag = 1;
							break;
						}
					} 	
				}
			}
			if (!flag){
				printf("palindrom: ");
				for(j = start; j < end; j++){
					printf("%c", _text[j]);
				}
				printf("\n");
			}
			i++;			
			start = end + 1; 
		}
		i++;	
	}
	return 0;
}
