#include <avr/io.h> // for register name
#include <util/delay.h> //for _delay_ms built-in

int main(void)
{
DDRB |= (1<<DD5);
DDRD &=~(1<<DD5);
PORTB = 0x00;
while(1)
{
  if((PIND&(1<<PD5))>>PD5){
	  PORTB &= ~(1<<PB5);
  }
  else{
	  PORTB |= (1<<PB5);
  }
}
}



