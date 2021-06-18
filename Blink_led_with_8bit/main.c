/*
 * main.c
 *
 *  Created on: Feb 15, 2020
 *      Author: marof
 */


#include <avr/io.h>
#include <util/delay.h>

int main(void){
	DDRD |= 0xFF;
    PORTD = 0x00;
    while(1){
    	PORTD = 0xAA ;
    	_delay_ms(1000);
    	PORTD = 0x55;
    	    	_delay_ms(1000);
    }
}
