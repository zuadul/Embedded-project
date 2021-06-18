#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

int main()
{
	DDRB = 0b00001111; //pb3 A,pb2 B,pb1 A',pb0 B'
	PORTB = 0x00;
   int stepSignal = 0;
	while(1){


		PORTB = 0b00001000; // A
		_delay_ms(10);
		PORTB = 0b00000100; // B
		_delay_ms(10);
		PORTB = 0b00000010; // A'
		_delay_ms(10);
		PORTB = 0b00000001; // B'
		_delay_ms(10);
		stepSignal++;
		if(stepSignal==128){
			_delay_ms(3000);
			stepSignal=0;
		}



	}
}
