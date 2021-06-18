/*
 * main.c
 *
 *  Created on: Feb 17, 2020
 *      Author: marof
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void){
	DDRB |=(1<<DD5);
	DDRD &=~(1<<DD5);
	PORTD |=(1<<PD5);
	PORTB=0x00;

	while(1){
		if((PIND&(1<<PD5))>>PD5){
			PORTB &= ~(1<<PB5);

		}
		else{
			PORTB |=(1<<PB5);
		}
	}
}
