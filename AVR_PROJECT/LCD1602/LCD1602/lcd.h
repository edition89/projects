/*
 * lcd.h
 *
 * Created: 04.08.2020 2:31:10
 *  Author: Роман
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "main.h"

void LCD_ini(void);
void setpos(unsigned char x, unsigned char y);
void str_lcd(char str1[]);

#endif /* LCD_H_ */