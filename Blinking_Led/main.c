/*
 * main.c
 *
 *  Created on: Feb 14, 2020
 *      Author: marof
 */
#include <avr/io.h>
#include <util/delay.h>

int main(void){
	DDRB |= (1<<DD5);
    PORTB = 0x00;
    while(1){
    	PORTB ^= _BV(PB5) ;
    	_delay_ms(1000);
    }
}

