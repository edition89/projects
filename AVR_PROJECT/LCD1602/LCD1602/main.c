/*
 * LCD1602.c
 *
 * Created: 01.08.2020 2:54:38
 * Author : Роман
 */ 
#include "main.h"

void port_ini(void){
	PORTD = 0x00;
	DDRD = 0xFF;
}

int main(void){
	port_ini();
	LCD_ini();
	setpos(0, 0);
	str_lcd("Hello World!");
	setpos(0, 1);
	str_lcd("String 2");
    while (1){
		
    }
}

