#include <avr/io.h> // for register name
#include <util/delay.h> //for _delay_ms built-in

int main(void)
{
DDRB = 0b00100000; // Set PB5 as ouput
PORTB = 0x00; //clear PortB
while(1) //Run for-ever
{
PORTB = 0b00100000; // Turn on
_delay_ms(500); //wait for 1 second
PORTB =0b00000000;// Turn off
_delay_ms(500);//wait for 1 second
}
}
