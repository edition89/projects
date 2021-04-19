/*
 * main.h
 *
 * Created: 04.08.2020 2:29:50
 *  Author: Роман
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"

#define e1 PORTD |= 0b00001000; //установка линии E в 1
#define e0 PORTD &= 0b11110111; //установка линии E в 0
#define rs1 PORTD |= 0b00000100; //установка линии E в 1
#define rs0 PORTD &= 0b11111011; //установка линии E в 0

#endif /* MAIN_H_ */