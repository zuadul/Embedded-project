/*
 * main.c
 *
 *  Created on: Feb 24, 2020
 *      Author: marof
 */


#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

int main(void)
{
	DDRD &= ~_BV(DDD2); //Set as input
	DDRB |= _BV(DDB5); // set as output
	PORTB= 0x00;

	while(1)
	{
		uint8_t count=0;
		if(bit_is_set(PIND,PIND2))//(PIND&(1<<PD2))
		{
		 count = 1;

			PORTB|= _BV(PORTB5);
			if(count==1){

			if(bit_is_set(PIND,PIND2)){
				PORTB &= ~_BV(PORTB5);
				count=0;
			}
			}



		}
	//	else
	//	{
	//		PORTB &= ~_BV(PORTB5);
	//	}
	}

}
