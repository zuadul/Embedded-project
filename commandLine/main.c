#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define F_CPU 16000000UL
#define F_OSC 16000000 //hz


///USART
#define BAUD 9600 /**< Baud Rate in bps. refer page 179 of 328p datasheet. */
#define MYUBRR F_OSC/16/BAUD-1 /**< UBRR = (F_CPU/(16*Baud))-1 for asynch USART page 179 328p datasheet. Baud rate 9600bps, assuming	16MHz clock UBRR0 becomes 0x0067*/
////////////////USART Start///////////////////////////////////////
void USART_init(unsigned int ubrr) {

	UCSR0C = (0 << USBS0) | (3 << UCSZ00); /// Step 1. Set UCSR0C in Asynchronous mode, no parity, 1 stop bit, 8 data bits
	UCSR0A = 0b00000000; /// Step 2. Set UCSR0A in Normal speed, disable multi-proc

	UBRR0H = (unsigned char) (ubrr >> 8); /// Step 3. Load ubrr into UBRR0H and UBRR0L
	UBRR0L = (unsigned char) ubrr;

	UCSR0B = 0b00011000; /// Step 4. Enable Tx Rx and disable interrupt in UCSR0B
}
int USART_send(char c, FILE *stream) {

	while (!( UCSR0A & (1 << UDRE0))) /// Step 1.  Wait until UDRE0 flag is high. Busy Waitinig
	{
		;
	}

	UDR0 = c; /// Step 2. Write char to UDR0 for transmission
}
int USART_receive( FILE *stream) {

	while (!(UCSR0A & (1 << RXC0)))
		/// Step 1. Wait for Receive Complete Flag is high. Busy waiting
		;

	return (UDR0); /// Step 2. Get and return received data from buffer
}
//////////////USART END

void pinMode(){
	unsigned char port;
	printf("\r\n");printf("\r\n");
	printf("enter the PORT name : 1 for PORTB and 2 for PORTD \r\n ");
	scanf("%c",&port);
	switch(port){
	case '1':
		printf("enter the value for configuration input or output PORTB...1 means input .2 means output\r\n");
		unsigned char in;
		scanf("%c",&in);
		if(in=='1'){
			printf("enter the pin number (0-5)\r\n");
			unsigned char pb;
			scanf("%c",&pb);
			switch(pb){
			case '0':
				DDRB &=~ (1<<PB0);
				printf("pin configure complete\r\n");
				break;
			case '1':
				DDRB &=~ (1<<PB1);
				printf("pin configure complete\r\n");
				break;
			case '2':
				DDRB &=~ (1<<PB2);
				printf("pin configure complete\r\n");
				break;
			case '3':
				DDRB &=~(1<<PB3);
				printf("pin configure complete\r\n");
				break;
			case '4':
				DDRB &=~ (1<<PB4);
				printf("pin configure complete\r\n");
				break;
			case '5':
				DDRB &=~ (1<<PB5);
				printf("pin configure complete\r\n");
				break;
			default:
				printf("you type %c ..pin not configure please try again.\r\n",pb);
				break;


			}

		}
		else if(in =='2'){
			printf("enter the pin number (0-5)\r\n");
						unsigned char po;
						scanf("%c",&po);
						switch(po){
						case '0':
							DDRB |= (1<<PB0);
							printf("pin configure complete\r\n");
							break;
						case '1':
							DDRB |= (1<<PB1);
							printf("pin configure complete\r\n");
							break;
						case '2':
							DDRB |= (1<<PB2);
							printf("pin configure complete\r\n");
							break;
						case '3':
							DDRB |=(1<<PB3);
							printf("pin configure complete\r\n");
							break;
						case '4':
							DDRB |= (1<<PB4);
							printf("pin configure complete\r\n");
							break;
						case '5':
							DDRB |= (1<<PB5);
							printf("pin configure complete\r\n");
							break;
						default:
							printf("you type %c ..pin not configure please try again\r\n",po);
							break;


						}
		}
		break;

	case '2':
		printf("enter the value for configuration input or output PORTD...1 means input.2 means output\r\n");
				unsigned char pd;
				scanf("%c",&pd);
				if(pd=='1'){
					printf("enter the pin number (2-7)\r\n");
					unsigned char pb;
					scanf("%c",&pb);
					switch(pb){
					case '2':
						DDRD &=~ (1<<PD2);
						printf("pin configure complete\r\n");
						break;
					case '3':
						DDRD &=~ (1<<PD3);
						printf("pin configure complete\r\n");
						break;
					case '4':
						DDRD &=~ (1<<PD4);
						printf("pin configure complete\r\n");
						break;
					case '5':
						DDRD &=~(1<<PD5);
						printf("pin configure complete\r\n");
						break;
					case '6':
						DDRD &=~ (1<<PD6);
						printf("pin configure complete\r\n");
						break;
					case '7':
						DDRD &=~ (1<<PD7);
						printf("pin configure complete\r\n");
						break;
					default:
						printf("you type %c ..pin not configure please try again\r\n",pb);
						break;


					}

				}
				else if(pd=='2'){
					printf("enter the pin number (2-7)\r\n");
								unsigned char po;
								scanf("%c",&po);
								switch(po){
								case '2':
									DDRB |= (1<<PD2);
									printf("pin configure complete\r\n");
									break;
								case '3':
									DDRB |= (1<<PD3);
									printf("pin configure complete\r\n");
									break;
								case '4':
									DDRB |= (1<<PD4);
									printf("pin configure complete\r\n");
									break;
								case '5':
									DDRB |=(1<<PD5);
									printf("pin configure complete\r\n");
									break;
								case '6':
									DDRB |= (1<<PD6);
									printf("pin configure complete\r\n");
									break;
								case '7':
									DDRB |= (1<<PD7);
									printf("pin configure complete\r\n");
									break;
								default:
									printf("you type %c ..pin not configure please try again.\r\n",po);
									break;


								}
					}


      break;
	default:
		printf("you don't read condition \r\n");
		break;
	}



}
void digitalWrite(){
	unsigned char port;
		printf("\r\n");printf("\r\n");
		printf("enter the PORT name : 1 for PORTB and 2 for PORTD \r\n ");
		scanf("%c",&port);
		switch(port){
		case '1':
			printf("enter the value for configuration PORTB output...1 means low .2 means high\r\n");
			unsigned char in;
			scanf("%c",&in);
			if(in=='1'){
				printf("enter the pin number (0-5)\r\n");
				unsigned char pb;
				scanf("%c",&pb);
				switch(pb){
				case '0':
					PORTB &=~ (1<<PB0);
					printf("pin configure complete\r\n");
					break;
				case '1':
					PORTB &=~ (1<<PB1);
					printf("pin configure complete\r\n");
					break;
				case '2':
					PORTB &=~ (1<<PB2);
					printf("pin configure complete\r\n");
					break;
				case '3':
					PORTB &=~(1<<PB3);
					printf("pin configure complete\r\n");
					break;
				case '4':
				    PORTB &=~ (1<<PB4);
					printf("pin configure complete\r\n");
					break;
				case '5':
					PORTB &=~ (1<<PB5);
					printf("pin configure complete\r\n");
					break;
				default:
					printf("you type %c ..pin not configure please try again.\r\n",pb);
					break;


				}

			}
			else if(in =='2'){
				printf("enter the pin number (0-5)\r\n");
							unsigned char po;
							scanf("%c",&po);
							switch(po){
							case '0':
								PORTB |= (1<<PB0);
								printf("pin configure complete\r\n");
								break;
							case '1':
								PORTB |= (1<<PB1);
								printf("pin configure complete\r\n");
								break;
							case '2':
								PORTB |= (1<<PB2);
								printf("pin configure complete\r\n");
								break;
							case '3':
								PORTB |=(1<<PB3);
								printf("pin configure complete\r\n");
								break;
							case '4':
								PORTB |= (1<<PB4);
								printf("pin configure complete\r\n");
								break;
							case '5':
								PORTB |= (1<<PB5);
								printf("pin configure complete\r\n");
								break;
							default:
								printf("you type %c ..pin not configure please try again\r\n",po);
								break;


							}
			}
			break;

		case '2':
			printf("enter the value for configuration output PORTD...1 means low.2 means high\r\n");
					unsigned char pd;
					scanf("%c",&pd);
					if(pd=='1'){
						printf("enter the pin number (2-7)\r\n");
						unsigned char pb;
						scanf("%c",&pb);
						switch(pb){
						case '2':
							PORTD &=~ (1<<PD2);
							printf("pin configure complete\r\n");
							break;
						case '3':
							PORTD &=~ (1<<PD3);
							printf("pin configure complete\r\n");
							break;
						case '4':
							PORTD &=~ (1<<PD4);
							printf("pin configure complete\r\n");
							break;
						case '5':
							PORTD &=~(1<<PD5);
							printf("pin configure complete\r\n");
							break;
						case '6':
							PORTD &=~ (1<<PD6);
							printf("pin configure complete\r\n");
							break;
						case '7':
							PORTD &=~ (1<<PD7);
							printf("pin configure complete\r\n");
							break;
						default:
							printf("you type %c ..pin not configure please try again\r\n",pb);
							break;


						}

					}
					else if(pd=='2'){
						printf("enter the pin number (2-7)\r\n");
									unsigned char po;
									scanf("%c",&po);
									switch(po){
									case '2':
										PORTD |= (1<<PD2);
										printf("pin configure complete\r\n");
										break;
									case '3':
										PORTD |= (1<<PD3);
										printf("pin configure complete\r\n");
										break;
									case '4':
										PORTD |= (1<<PD4);
										printf("pin configure complete\r\n");
										break;
									case '5':
										PORTD |=(1<<PD5);
										printf("pin configure complete\r\n");
										break;
									case '6':
										PORTD |= (1<<PD6);
										printf("pin configure complete\r\n");
										break;
									case '7':
										PORTD |= (1<<PD7);
										printf("pin configure complete\r\n");
										break;
									default:
										printf("you type %c ..pin not configure please try again.\r\n",po);
										break;


									}
						}


	      break;
		default:
			printf("you don't read condition \r\n");
			break;
		}
}
void digitalRead(){
	printf("\r\n");

	unsigned char port;
			printf("\r\n");printf("\r\n");
			printf("enter the PORT name : 1 for PORTB and 2 for PORTD \r\n ");
			scanf("%c",&port);
			switch(port){
			case '1':

					printf("enter the pin number (0-5)\r\n");
					unsigned char pb;
					scanf("%c",&pb);
					switch(pb){
					case '0':
						if((PINB&(1<<PB0))>>PB0){
							printf("PB 0 is output\r\n");
						}
						else{
							printf("PB 0 is input\r\n");
						}
						break;
					case '1':
						if((PINB&(1<<PB1))>>PB1){
							printf("PB 1 is output\r\n");
						}
						else{
							printf("PB 1 is input\r\n");
						}
						break;
					case '2':
						if((PINB&(1<<PB2))>>PB2){
													printf("PB 2 is output\r\n");
												}
												else{
													printf("PB 2 is input\r\n");
												}
						break;
					case '3':
						if((PINB&(1<<PB3))>>PB3){
													printf("PB 3 is output\r\n");
												}
												else{
													printf("PB 3 is input\r\n");
												}
						break;
					case '4':
						if((PINB&(1<<PB4))>>PB4){
													printf("PB 4 is output\r\n");
												}
												else{
													printf("PB 4 is input\r\n");
												}
						break;
					case '5':
						if((PINB&(1<<PB5))>>PB5){
													printf("PB 5 is output\r\n");
												}
												else{
													printf("PB 5 is input\r\n");
												}
						break;
					default:
						printf("you type %c ..pin not configure please try again.\r\n",pb);
						break;


					}


				break;

			case '2':

							printf("enter the pin number (2-7)\r\n");
							unsigned char pc;
							scanf("%c",&pc);
							switch(pc){
							case '2':
								if((PIND&(1<<PD2))>>PD2){
															printf("PD 2 is output\r\n");
														}
														else{
															printf("PD 2 is input\r\n");
														}
								break;
							case '3':
								if((PIND&(1<<PD3))>>PD3)
								{
								printf("PD 3 is output\r\n");
								}
							else{
							   printf("PD 3 is input\r\n");
								}
								break;
							case '4':
								if((PIND&(1<<PD4))>>PD4)
																{
																printf("PD 4 is output\r\n");
																}
															else{
															   printf("PD 4 is input\r\n");
																}
								break;
							case '5':
								if((PIND&(1<<PD5))>>PD5)
																{
																printf("PD 5 is output\r\n");
																}
															else{
															   printf("PD 5 is input\r\n");
																}
								break;
							case '6':
								if((PIND&(1<<PD6))>>PD6)
																{
																printf("PD 6 is output\r\n");
																}
															else{
															   printf("PD 6 is input\r\n");
																}
								break;
							case '7':
								if((PIND&(1<<PD7))>>PD7)
																{
																printf("PD 7 is output\r\n");
																}
															else{
															   printf("PD 7 is input\r\n");
																}
								break;
							default:
								printf("you type %c ..pin not configure please try again\r\n",pb);
								break;


							}






		      break;
			default:
				printf("you don't read condition \r\n");
				break;
			}

/*DDRD |= (1<<DD5); //PD5 is output
printf("digitalRead() configure complete\r\n");
if((PIND&(1<<PD5))>>PD5){
	printf("PD 5 is output\r\n");
}
else{
	printf("PD 5 is input\r\n");
}
*/

}

void init_ADC()
{
	/// ADMUX section 23.9.1 page 262
	///BIT 7 and BIT 6 – AVCC with external capacitor at AREF pin REFS0 =0 and REFS1= 1
	/// BIT 5 – ADC Left Adjust Result ADLAR = 0
    /// BIT 3:0 –MUX3:0 0b0000 for channel 0
	ADMUX = 0b01000000;
	//same as previous line
	//	ADMUX = (_BV(REFS0))| (ADMUX & ~_BV(REFS1))|(_BV(ADLAR))|(ADMUX & ~_BV(MUX3))|(ADMUX & ~_BV(MUX2))|(ADMUX & ~_BV(MUX1))|(ADMUX & ~_BV(MUX0));

	///DIDR0 – Digital Input Disable Register 0 section Section 23.9.4 page 265 - 266
	/// Disable digital input buffer of ADC0 to save power consumption
	DIDR0 = 0b00000001;

	/// ADSCRA ADC Control and Status Register A Section 23.9.2 page 263 -264
	///Bit 7 – ADEN: ADC Enable =1 enable ADC
	///Bit 6 – ADSC: ADC Start Conversion =0 do not start conversion
	///Bit 5 – ADATE: ADC Auto Trigger Enable = 0 Disable trigger
	///Bit 4 – ADIF: ADC Interrupt Flag = 0
	///Bit 3 – ADIE: ADC Interrupt Enable = 0 Disable ADC interrupt
	///Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits 010 division factor = 4
	ADCSRA = 0b10000010;

}
void init_ADC1()
{
	ADMUX = 0b01000001;  /// BIT 3:0 –MUX3:0 0b0001 for channel 1
	DIDR0 = 0b00000001;
	ADCSRA = 0b10000010;

}
void init_ADC2()
{
	ADMUX = 0b01000010;  /// BIT 3:0 –MUX3:0 0b0010 for channel 2
	DIDR0 = 0b00000001;
	ADCSRA = 0b10000010;

}
void init_ADC3()
{
	ADMUX = 0b01000011;  /// BIT 3:0 –MUX3:0 0b0011 for channel 3
	DIDR0 = 0b00000001;
	ADCSRA = 0b10000010;

}
void init_ADC4()
{
	ADMUX = 0b01000100;  /// BIT 3:0 –MUX3:0 0b0100 for channel 4
	DIDR0 = 0b00000001;
	ADCSRA = 0b10000010;

}
void init_ADC5()
{
	ADMUX = 0b01000101;  /// BIT 3:0 –MUX3:0 0b0101 for channel 5
	DIDR0 = 0b00000001;
	ADCSRA = 0b10000010;

}
void analogRead(){

  printf("enter the channel or PORTC no (0-5)\r\n");
  unsigned char ch;
  scanf("%c",&ch);
  switch(ch){
  case '0':
	  init_ADC();
	   int result;
	  	//USART_init(MYUBRR);
	  	//stdout = fdevopen(USART_send, NULL);
	  	//	stdin = fdevopen(NULL, USART_receive);


	  		ADCSRA |= (1<<ADSC);
	  		while (bit_is_set(ADCSRA,ADSC))
	  		{
	  			;
	  		}
	  		result = ADC;
	  		printf("\r\n");
	  		printf("Result %d\r\n",result);
	  		_delay_ms(100);
	  		break;
  case '1':
	  init_ADC1();
	   int result1;
	  	//USART_init(MYUBRR);
	  	//stdout = fdevopen(USART_send, NULL);
	  	//	stdin = fdevopen(NULL, USART_receive);


	  		ADCSRA |= (1<<ADSC);
	  		while (bit_is_set(ADCSRA,ADSC))
	  		{
	  			;
	  		}
	  		result1 = ADC;
	  		printf("\r\n");
	  		printf("Result %d\r\n",result1);
	  		_delay_ms(100);
	  		break;
  case '2':
	  init_ADC2();
	   int result2;
	  	//USART_init(MYUBRR);
	  	//stdout = fdevopen(USART_send, NULL);
	  	//	stdin = fdevopen(NULL, USART_receive);


	  		ADCSRA |= (1<<ADSC);
	  		while (bit_is_set(ADCSRA,ADSC))
	  		{
	  			;
	  		}
	  		result2 = ADC;
	  		printf("\r\n");
	  		printf("Result %d\r\n",result2);
	  		_delay_ms(100);
	  		break;
  case '3':
	  init_ADC3();
	   int result3;
	  	//USART_init(MYUBRR);
	  	//stdout = fdevopen(USART_send, NULL);
	  	//	stdin = fdevopen(NULL, USART_receive);


	  		ADCSRA |= (1<<ADSC);
	  		while (bit_is_set(ADCSRA,ADSC))
	  		{
	  			;
	  		}
	  		result3 = ADC;
	  		printf("\r\n");
	  		printf("Result %d\r\n",result3);
	  		_delay_ms(100);
	  		break;
  case '4':
	  init_ADC4();
	   int result4;
	  	//USART_init(MYUBRR);
	  	//stdout = fdevopen(USART_send, NULL);
	  	//	stdin = fdevopen(NULL, USART_receive);


	  		ADCSRA |= (1<<ADSC);
	  		while (bit_is_set(ADCSRA,ADSC))
	  		{
	  			;
	  		}
	  		result4 = ADC;
	  		printf("\r\n");
	  		printf("Result %d\r\n",result4);
	  		_delay_ms(100);
	  		break;
  case '5':
	  init_ADC5();
	   int result5;
	  	//USART_init(MYUBRR);
	  	//stdout = fdevopen(USART_send, NULL);
	  	//	stdin = fdevopen(NULL, USART_receive);


	  		ADCSRA |= (1<<ADSC);
	  		while (bit_is_set(ADCSRA,ADSC))
	  		{
	  			;
	  		}
	  		result5 = ADC;
	  		printf("\r\n");
	  		printf("Result %d\r\n",result5);
	  		_delay_ms(100);
	  		break;
  default:
	  printf("you type %c . this is not defined\r\n",ch);
  }




}

int main() {

	unsigned char command;
	USART_init(MYUBRR);

	// Initialise the standard IO handlers
	stdout = fdevopen(USART_send, NULL);
	stdin = fdevopen(NULL, USART_receive);
	printf("initialized\r\n");
	while (1) {
		printf("For pinMode() type 1 \r\n");
		printf("For digitalWrite() type 2 \r\n");
		printf("For digitalRead() type 3 \r\n");
		printf("For analogRead() type 4 \r\n");
		scanf("%c", &command);
		switch (command) {
		case '1':
			pinMode();
			printf("pinMode() is called successfully \r\n");
			break;
		case '2':
			digitalWrite();
			printf("digitalWrite() is called successfully\r\n");
			break;
		case '3':
			digitalRead();
			printf("digitalRead() is called successfully\r\n");
			break;
		case '4':
			analogRead();
			printf("analogRead() is called successfully\r\n");
			break;
		default:
			printf("received %c\r\n", command);
			break;

		}

   printf("\r\n");

		_delay_ms(500);
		printf("\r\n");
	}
}

