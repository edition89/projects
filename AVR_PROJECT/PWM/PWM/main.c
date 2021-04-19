/*
 * PWM.c
 *
 * Created: 05.08.2020 2:13:15
 * Author : Роман
 */ 

#include "main.h"


void port_ini(void){
	PORTB = 0x00;
	DDRB = 0b00001000;
}

int main(void)
{
	unsigned char pwm_state = 0;
    port_ini();
	init_PWM_timer();
	OCR2 = 50;
    while (1){
		if(!pwm_state){
			OCR2++;
			if(OCR2 > 254) pwm_state = 1;
		}
		else{
			OCR2--;
			if(OCR2 < 1) pwm_state = 0;
		}
		_delay_ms(5);
    }
}

