#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

// Write a simple program to animate 8 LEDs connected to PORT B from right to left

int main(void)
{
    unsigned char c = 0x01;
    DDRB= 0xFF;
    uint8_t i;
    while(1)
    {
	    PORTB = c ;
	    c=c<<1;
	     if(c==1<<7) c=c>>1;
	    _delay_ms (1000) ;

    }
}
