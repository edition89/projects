/*
 * PWM.c
 *
 * Created: 05.08.2020 2:16:26
 *  Author: Роман
 */ 
#include "PWM.h"

void init_PWM_timer(void){
	ASSR = 0x00;
	TCCR2 = 0b01101110; //Fast PWM, Clear OC2 on Compare Match, clkT2S/256 (From Prescaler) (реальная частота получится 8мгц/256 = 31250 Гц)
	TCNT2 = 0x00; // Timer Value = 0
	OCR2 = 0;//Скважность 0
	TIMSK |= 0x00; //
}