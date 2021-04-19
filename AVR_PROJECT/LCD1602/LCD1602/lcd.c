/*
 * lcd.c
 *
 * Created: 04.08.2020 2:32:18
 *  Author: Роман
 */ 
#include "lcd.h"

void sendhalfbyte(unsigned char c){
	c <<= 4;
	e1;
	_delay_us(50);
	PORTD &= 0b00001111; //Стираем информацию на информационных входах
	PORTD |= c;
	e0;
	_delay_us(50);
}

void sendbyte(unsigned char c, unsigned char mode){
	if(mode == 0) rs0;
	if(mode == 1) rs1;
	unsigned char hc = 0;
	hc = c >> 4;
	sendhalfbyte(hc); sendhalfbyte(c);
}

void sendchar(unsigned char c){
	sendbyte(c, 1);
}

void setpos(unsigned char x, unsigned char y){
	char adress;
	adress = (0x40*y+x)|0b10000000;
	sendbyte(adress, 0);
	
}

void LCD_ini(void){
	_delay_ms(15);
	sendhalfbyte(0b00000011);
	_delay_ms(4);
	sendhalfbyte(0b00000011);
	_delay_us(100);
	sendhalfbyte(0b00000011);
	_delay_ms(1);
	sendhalfbyte(0b00000010);
	_delay_ms(1);
	sendbyte(0b00101000, 0); // 4 битный режим, 2 линии (N = 1)
	_delay_ms(1);
	sendbyte(0b00001100, 0); //включаем изображение на дисплее (D = 1), курсоры никаие не включаем
	_delay_ms(1);
	sendbyte(0b00000110, 0); //заставляем курсор двигаться справа налево
	_delay_ms(1);
}

void clearlcd(){
	sendbyte(0x01, 0);
	_delay_us(1500);
}

void str_lcd(char str1[]){
	wchar_t n;
	for(n = 0; str1[n] != '\0'; n++) sendchar(str1[n]);
}
