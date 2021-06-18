/*
 * main.c
 *
 *  Created on: Aug 29, 2019
 *      Author: marof
 */


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define F_CPU 16000000UL


#define FOSC 16000000 /**< Clock speed for UBRR calculation. refer page 179 of 328p datasheet. */
#define BAUD 9600 /**< Baud Rate in bps. refer page 179 of 328p datasheet. */
#define MYUBRR FOSC/16/BAUD-1 /**< UBRR = (F_CPU/(16*Baud))-1 for asynch USART page 179 328p datasheet. Baud rate 9600bps, assuming	16MHz clock UBRR0 becomes 0x0067*/
int result;
#define LEDs_DDR DDRC
#define LEDs_PORT PORTC
#define LED0 PC0
#define LED1 PC1
#define LED2 PC2
#define LED3 PC3
#define LED4 PC4
#define LED5 PC5
/**
 * @brief Initialize USART for 8 bit data transmit no parity and 1 stop bit.
 *
 *@details This is a code snippet from datasheet page 182
 *
 * @param ubrr The UBRR value calculated in macro MYUBRR
 * @see MYUBRR
 */
void USART_init(unsigned int ubrr)
{

	UCSR0C = (0<<USBS0)|(3<<UCSZ00); /// Step 1. Set UCSR0C in Asynchronous mode, no parity, 1 stop bit, 8 data bits
	UCSR0A = 0b00000000;/// Step 2. Set UCSR0A in Normal speed, disable multi-proc

	UBRR0H = (unsigned char)(ubrr>>8);/// Step 3. Load ubrr into UBRR0H and UBRR0L
	UBRR0L = (unsigned char)ubrr;


	UCSR0B = 0b00011000;/// Step 4. Enable Tx Rx and disable interrupt in UCSR0B
}

/**
 * @brief Send 8bit data.http://127.0.0.1:1880/
 *
 *@details This is a code snippet from datasheet page 184
 *
 * @param data The 8 bit data to be sent
 */

int USART_send(char c, FILE *stream)
{

	while ( !( UCSR0A & (1<<UDRE0)) )/// Step 1.  Wait until UDRE0 flag is high. Busy Waitinig
	{;}

	UDR0 = c; /// Step 2. Write char to UDR0 for transmission
}

/**
 * @brief Receive 8bit sata.
 *
 *@details This is a code snippet from datasheet page 187
 *
 * @return Returns received data from UDR0
 */
int USART_receive(FILE *stream )
{

	while ( !(UCSR0A & (1<<RXC0)) )/// Step 1. Wait for Receive Complete Flag is high. Busy waiting
		;

	return UDR0;/// Step 2. Get and return received data from buffer
}

void init_ADC()
{
	/// ADMUX section 23.9.1 page 262
	///BIT 7 and BIT 6 – AVCC with external capacitor at AREF pin REFS0 =0 and REFS1= 1
	/// BIT 5 – ADC Left Adjust Result ADLAR = 0
    /// BIT 3:0 –MUX3:0 0b0000 for channel 0
	ADMUX = 0b01000001;
	//same as previous line
	//	ADMUX = (_BV(REFS0))| (ADMUX & ~_BV(REFS1))|(_BV(ADLAR))|(ADMUX & ~_BV(MUX3))|(ADMUX & ~_BV(MUX2))|(ADMUX & ~_BV(MUX1))|(ADMUX & ~_BV(MUX0));

	///DIDR0 – Digital Input Disable Register 0 section Section 23.9.4 page 265 - 266
	/// Disable digital input buffer of ADC0 to save power consumption
	//DIDR0 = 0b00000001;

	/// ADSCRA ADC Control and Status Register A Section 23.9.2 page 263 -264
	///Bit 7 – ADEN: ADC Enable =1 enable ADC
	///Bit 6 – ADSC: ADC Start Conversion =0 do not start conversion
	///Bit 5 – ADATE: ADC Auto Trigger Enable = 0 Disable trigger
	///Bit 4 – ADIF: ADC Interrupt Flag = 0
	///Bit 3 – ADIE: ADC Interrupt Enable = 0 Disable ADC interrupt
	///Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits 010 division factor = 4
	ADCSRA = 0b10000010;

}
void init_LEDs() {
	LEDs_DDR |= (1 << LED0) | (1 << LED1) | (1 << LED2) | (1 << LED3)
			| (1 << LED4) | (1 << LED5);
	LEDs_PORT &= ~(1 << LED0) | ~(1 << LED1) | ~(1 << LED2) | ~(1 << LED3)
			| ~(1 << LED4) | ~(1 << LED5);
}
int main()
{

	init_ADC();
	init_LEDs();
	unsigned char command;
	unsigned char joy;
	USART_init(MYUBRR);
	stdout = fdevopen(USART_send, NULL);
		stdin = fdevopen(NULL, USART_receive);

	while(1)
	{  sacnf("%c", &joy);
		if(joy==1){
		ADCSRA |= (1<<ADSC);
		while (bit_is_set(ADCSRA,ADSC))
		{
			;
		}
		result = ADC;
		//printf("{\"adc0\":%d}\n",result);
		printf("{\"adc%d\":%d}\n",bit_is_set(ADMUX,0),result);
		ADMUX^=(1<<0);
		_delay_ms(300);}
	else {
		scanf("%c", &command);
				switch (command) {
				case '0':
					LEDs_PORT ^= (1 << LED0);
					printf("LED0 is %d\r\n",(LEDs_PORT&(1<<LED0))>>LED0);
					break;
				case '1':
					LEDs_PORT ^= (1 << LED1);
					printf("LED1 is %d\r\n",(LEDs_PORT&(1<<LED1))>>LED1);
					break;
				case '2':
					LEDs_PORT ^= (1 << LED2);
					printf("LED2 is %d\r\n",(LEDs_PORT&(1<<LED2))>>LED2);
					break;
				case '3':
					LEDs_PORT ^= (1 << LED3);
					printf("LED3 is %d\r\n",(LEDs_PORT&(1<<LED3))>>LED3);
					break;
				case '4':
					LEDs_PORT ^= (1 << LED4);
					printf("LED4 is %d\r\n",(LEDs_PORT&(1<<LED4))>>LED4);
					break;
				case '5':
					LEDs_PORT ^= (1 << LED5);
					printf("LED5 is %d\r\n",(LEDs_PORT&(1<<LED5))>>LED5);
					break;
				default:
					printf("received %c\r\n", command);
					break;

				}



				_delay_ms(100);

	}

	}
}


