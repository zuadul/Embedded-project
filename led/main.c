#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

// Write a simple program to animate 8 LEDs connected to PORT B from right to left

int main(void)
{
    unsigned char c = 0x01;
    DDRB= 0xFF;
    while(1)
    {
	    PORTB = c ;
	    if(c==1<<7)c = 1;
	    else c = c << 1;
	    _delay_ms (1000) ;
    }
}


