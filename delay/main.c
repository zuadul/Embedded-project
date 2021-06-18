/*
 * main.c
 *
 *  Created on: Aug 28, 2019
 *      Author: marof
 */


#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#define F_CPU 16000000UL


#define FOSC 16000000 //!< Clock speed for UBRR calculation. refer page 179 of 328p datasheet.
#define BAUD 9600 //!< Baud Rate in bps. refer page 179 of 328p datasheet.
#define MYUBRR FOSC/16/BAUD-1 //!< UBRR = (F_CPU/(16*Baud))-1 for asynch USART page 179 328p datasheet. Baud rate 9600bps, assuming	16MHz clock UBRR0 becomes 0x0067

#define OUR_DELAY 30 //!< 19+09+02 our last 2 digit Id number sum

volatile uint32_t n; //!< n to count overflows of timer01 (used in computing elapsed time)

/**
 *	@brief Initializing USART
 *
 */
void USART_init(unsigned int ubrr)
{

	UCSR0C = (0<<USBS0)|(3<<UCSZ00); //! Step 1. Set UCSR0C in Asynchronous mode, no parity, 1 stop bit, 8 data bits
	UCSR0A = 0b00000000;//! Step 2. Set UCSR0A in Normal speed, disable multi-proc

	UBRR0H = (unsigned char)(ubrr>>8);//! Step 3. Load ubrr into UBRR0H and UBRR0L
	UBRR0L = (unsigned char)ubrr;


	UCSR0B = 0b00011000;//! Step 4. Enable Tx Rx and disable interrupt in UCSR0B
}

/**
 * @brief Send 8bit data.
 *
 *
 */
int USART_send(char c, FILE *stream)
{

	while ( !( UCSR0A & (1<<UDRE0)) )//! Step 1.  Wait until UDRE0 flag is high. Busy Waitinig
	{;}

	UDR0 = c; //! Step 2. Write char to UDR0 for transmission
}

/**
 *	@brief function to receive 8-bit data
 *
 * 	@return Returns received data from UDR0
 */

int USART_receive(FILE *stream )
{

	while ( !(UCSR0A & (1<<RXC0)) )//! Step 1. Wait for Receive Complete Flag is high. Busy waiting
		;

	return UDR0;//! Step 2. Get and return received data from buffer
}

/**
 * @brief ISR for  TIMER1 overflow. Increase value of n.
*/
ISR(TIMER1_OVF_vect)
{
	n++;
	//printf("Current n = %"PRId32"\n", n);
}

/**
 *  @brief Initialization of TIMER 01
 * */
void timer1_init()
{

	TCCR1A = 0b00000000; ///Step 1.  normal mode
	TCCR1B = 0b00000011; ///Step 2. 1:64 prescaler, internal clock
	TIMSK1 = 0b00000001; ///Step 3. enable Timer 1 overflow interrupt
}




void blocking_delay_microseconds(uint32_t _delay){
	uint32_t delay = _delay; /// _delay : in microseconds
	uint32_t elapsed_time;
	uint32_t last_time = 0;
	uint32_t n = 0;
	TCNT1 = 0; /// TCNT1 = 0 : resetting timer
	cli(); /// cli() : Global interrupt disable. Nothing can stop the following code
	while(1){
		/// If timer has overflown, its last value would be bigger than current value.
		/// We check overflow this way without invokation of interrupt
		if (last_time > TCNT1){
			n++;
		}
		last_time = TCNT1;
		elapsed_time = n * 262144 + (uint32_t) (TCNT1*4);  /// Target Period = ((2 ^ 16) * (Prescale / 16000000) = ((2 ^ 16) * (64 / 16000000) = 0.262144 = 262144 uS (approx.) TCNT1 1 is 4uS
		if (elapsed_time >= delay){ /// if interval has passed, then break
			break;
		}
	}
	sei(); /// global interrupt is enabled again
}



void blocking_delay_milliseconds(uint32_t _delay){
	uint32_t delay = _delay * 1000; /// _delay * 1000 : Converting to milliseconds
	uint32_t elapsed_time;
	uint32_t last_time = 0;
	uint32_t n = 0;
	TCNT1 = 0; /// TCNT1 = 0 : resetting timer
	cli(); /// cli() : Global interrupt disable. Nothing can stop the following code
	while(1){
		/// If timer has overflown, its last value would be bigger than current value.
		/// We check overflow this way without invokation of interrupt
		if (last_time > TCNT1){
					n++;
				}
				last_time = TCNT1;
		elapsed_time = n * 262144 + (uint32_t) (TCNT1*4);  /// Target Period = ((2 ^ 16) * (Prescale / 16000000) = ((2 ^ 16) * (64 / 16000000) = 0.262144 = 262144 uS (approx.) TCNT1 1 is 4uS
		if (elapsed_time >= delay){ /// if interval has passed, then break
			break;
		}
	}
	sei(); /// global interrupt is enabled again
}


void blocking_delay_seconds(uint32_t _delay){
	uint32_t delay = _delay * 1000000; /// _delay * 1000000 : converting to seconds
	uint32_t elapsed_time;
	uint32_t last_time = 0;
	uint32_t n = 0;
	TCNT1 = 0; /// TCNT1 = 0 : resetting timer
	cli(); /// cli() : Global interrupt disable. Nothing can stop the following code
	while(1){
		/// If timer has overflown, its last value would be bigger than current value.
		/// We check overflow this way without invokation of interrupt
		if (last_time > TCNT1){
			n++;
		}
		last_time = TCNT1;
		elapsed_time = n * 262144 + (uint32_t) (TCNT1*4);  /// Target Period = ((2 ^ 16) * (Prescale / 16000000) = ((2 ^ 16) * (64 / 16000000) = 0.262144 = 262144 uS (approx.) TCNT1 1 is 4uS
		if (elapsed_time >= delay){ /// if interval has passed, then break
			break;
		}
	}
	sei(); /// global interrupt is enabled again
}

/**
 * @brief Function for non-blocking delay for given microseconds
 * @details This uses global interrupt enable so the CPU is allowed to execute other work while the timer will go up concurrently
 * */
void non_blocking_delay_microseconds(uint32_t _delay){
	uint32_t delay = _delay; /// _delay : in microseconds
	uint32_t elapsed_time;
	n = 0;
	TCNT1 = 0; /// TCNT1 = 0 : resetting timer
	sei(); /// sei() : Global interrupt is enabled. Thus the code is not blocking processor
	while(1){
		elapsed_time = n * 262144 + (uint32_t) (TCNT1*4);  /// Target Period = ((2 ^ 16) * (Prescale / 16000000) = ((2 ^ 16) * (64 / 16000000) = 0.262144 = 262144 uS (approx.) TCNT1 1 is 4uS


		if (elapsed_time >= delay){ /// if interval has passed, then break
			break;
		}
	}
}


void non_blocking_delay_milliseconds(uint32_t _delay){
	uint32_t delay = _delay * 1000; /// _delay * 1000 : converting to milliseconds
	uint32_t elapsed_time;
	n = 0;
	TCNT1 = 0; /// TCNT1 = 0 : resetting timer
	sei(); /// sei() : Global interrupt is enabled. Thus the code is not blocking processor
	while(1){
		elapsed_time = n * 262144 + (uint32_t) (TCNT1*4);  /// Target Period = ((2 ^ 16) * (Prescale / 16000000) = ((2 ^ 16) * (64 / 16000000) = 0.262144 = 262144 uS (approx.) TCNT1 1 is 4uS




		if (elapsed_time >= delay){ /// if interval has passed, then break
			break;
		}
	}
}


void non_blocking_delay_seconds(uint32_t _delay){
	uint32_t delay = _delay * 1000000; /// _delay * 1000000 : converting to seconds
	uint32_t elapsed_time;
	n = 0;
	TCNT1 = 0; /// TCNT1 = 0 : resetting timer
	sei(); /// sei() : Global interrupt is enabled. Thus the code is not blocking processor
	while(1){
		elapsed_time = n * 262144 + (uint32_t) (TCNT1*4);  /// Target Period = ((2 ^ 16) * (Prescale / 16000000) = ((2 ^ 16) * (64 / 16000000) = 0.262144 = 262144 uS (approx.) TCNT1 1 is 4uS



		if (elapsed_time >= delay){ /// if interval has passed, then break
			break;
		}
	}
}




int main()
{
	unsigned char command;
	USART_init(MYUBRR);
	timer1_init(); /// Initializing TIMER01 (16-bit timer)

	stdout = fdevopen(USART_send, NULL); /// Initialize the standard IO handlers for printf
	stdin = fdevopen(NULL, USART_receive);/// Initialize the standard IO handlers for scanf
	printf("Initialized\n");
	n = 0; // reset n
	TCNT1 = 0; // reset Timer 1
	sei();
	printf("OUR DELAY = %d\n", (int)OUR_DELAY);
	while(1)
	{

		printf("1 for blocking delay us\r\n");
				printf("2 for blocking delay ms\r\n");
				printf("3 for blocking delay s\r\n");
				printf("4 for non blocking delay us\r\n");
				printf("5 for non blocking delay ms\r\n");
				printf("6 for non blocking delay s\r\n");
		scanf("%c", &command);

		switch(command){
		case '1':
			printf("blocking delay %d microseconds\r\n", OUR_DELAY);
					blocking_delay_microseconds(OUR_DELAY);
					break;
		case '2':
			printf("blocking delay %d milliseconds\r\n", OUR_DELAY);
					blocking_delay_milliseconds(OUR_DELAY);
					break;
		case '3':
			printf("blocking delay %d seconds\r\n", OUR_DELAY);
					blocking_delay_seconds(OUR_DELAY);
					break;
		case '4':
			printf("non-blocking delay %d microseconds\r\n", OUR_DELAY);
					non_blocking_delay_microseconds(OUR_DELAY);
			break;
		case '5':
			printf("non-blocking delay %d milliseconds\r\n", OUR_DELAY);
					non_blocking_delay_milliseconds(OUR_DELAY);
					break;
		case '6':
			printf("non-blocking delay %d seconds\r\n", OUR_DELAY);
					non_blocking_delay_seconds(OUR_DELAY);
					break;
		default:
			printf("non initialized\r\n",command);
		}


	}
}
