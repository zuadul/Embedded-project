/*
 * main.c
 *
 *  Created on: Feb 22, 2020
 *      Author: marof
 */

#include <avr/io.h>

#include <util/delay.h>


int main(void){
	DDRD |= 0xFF;
	    PORTD = 0x00;

	    DDRC |=0b00000011;
	  while(1){
	    PORTC =0x00;
	    PORTC = 0b00000001;
	    PORTD = 0b00000100;

	    _delay_ms(200);
	    PORTD = 0b00000000;
	    PORTD = 0b00000100;
	    _delay_ms(200);

	    PORTD = 0b00000000;
	    PORTD = 0b00010000;
	    _delay_ms(200);

	    PORTD = 0b00000000;
	    PORTD = 0b00100000;
	    _delay_ms(200);
	    PORTC = 0b00000010;

	    PORTD = 0b00010000;
	     _delay_ms(200);

	     PORTD = 0b00010000;

	      _delay_ms(200);


	       PORTD = 0b00000100;
	       _delay_ms(200);


	       PORTD = 0b00001000;
	        _delay_ms(200);

	        PORTD = 0b00000000;
	        PORTC = 0b00000000;
	         _delay_ms(200);

	         PORTD = 0b00000000;
	         PORTD = 0b00001000;
	          _delay_ms(200);

	          PORTD = 0b00000000;

	          _delay_ms(200);

	          PORTD = 0b00011110;
	          _delay_ms(200);















	  }


}
