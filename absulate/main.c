/*
 * main.c
 *
 *  Created on: Aug 30, 2019
 *      Author: marof
 */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <inttypes.h>

#define F_CPU 16000000UL

#define FOSC 16000000 //!< Clock speed for UBRR calculation. refer page 179 of 328p datasheet.
#define BAUD 9600 //!< Baud Rate in bps. refer page 179 of 328p datasheet.
#define MYUBRR FOSC/16/BAUD-1 //!< UBRR = (F_CPU/(16*Baud))-1 for asynch USART page 179 328p datasheet. Baud rate 9600bps, assuming	16MHz clock UBRR0 becomes 0x0067
#define slot_count 20
#define step_size 5.625 //!< Angle the motor moves by in one step

volatile int count = 0;
volatile float angle = 0.0;
volatile int startValue = 0;
volatile int endValue = 63;
uint8_t flag = 0; /// Variable to store if a new command is issued

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
 * @brief Interrupt Service Routine to get slot counts of motor (position)
 * */
ISR(INT0_vect) {
	angle += step_size;
	if (count < slot_count) count++;
	else count = 0;
	flag = 1;
}

/**
 * @brief Function to initialize interrupt pin 0 for Pin Change Interrupt
 * */
void init_int0() {
	DDRD &= ~(1 << DDD2); /// Set int0 as input
	PORTD |= (1 << PD2); /// pullup
	EICRA &= ~(1 << ISC01); /// PIN Change Interrupt ; ISC01, ISC00 = 0,1 ; Any logical change will generate interrupt
	EICRA |= (1 << ISC00);
	EIMSK |= (1 << INT0); /// Enable INT0
}

/**
 * @brief Initializing ADC. We will read input from A0 (using the variable ADC)
 * */
void init_ADC()
{
	ADMUX = 0b01000000;
	DIDR0 = 0b00000001;
	ADCSRA = 0b10000010;
}


/// Step sequence array for 64 steps (not tested)
uint8_t graycode_table[64]={
		0b00000000, 0b00000001, 0b00000011, 0b00000010,
		0b00000110, 0b00000111, 0b00000101, 0b00000100,
		0b00001100, 0b00001101, 0b00001111, 0b00001110,
		0b00001010, 0b00001011, 0b00001001, 0b00001000,
		0b00011000, 0b00011001, 0b00011011, 0b00011010,
		0b00011110, 0b00011111, 0b00011101, 0b00011100,
		0b00010100, 0b00010101, 0b00010111, 0b00010110,
		0b00010010, 0b00010011, 0b00010001, 0b00010000,
		0b00110000, 0b00110001, 0b00110011, 0b00110010,
		0b00110110, 0b00110111, 0b00110101, 0b00110100,
		0b00111100, 0b00111101, 0b00111111, 0b00111110,
		0b00111010, 0b00111011, 0b00111001, 0b00111000,
		0b00101000, 0b00101001, 0b00101011, 0b00101010,
		0b00101110, 0b00101111, 0b00101101, 0b00101100,
		0b00100100, 0b00100101, 0b00100111, 0b00100110,
		0b00100010, 0b00100011, 0b00100001, 0b00100000

};


void moveMotor(float next_angle){
	uint8_t steps;
	if (angle < next_angle){
		steps = (next_angle - angle) / 7.5;
	}
	else{
		steps = (360 - angle + next_angle) / 7.5;
	}


    while(startValue>endValue)
    {   uint8_t i=0;
    	 angle = graycode_table[i];
    	i++;
    	startValue++;

    }
	flag = 0; // make flag = 0, command is performed.
}


float Map (float value, float currentMin, float currentMax, float outMin, float outMax){
	return ( value * ( (outMax - outMin) / (currentMax - currentMin) ) + outMin );
}


int main() {

	USART_init(MYUBRR);
	stdout = fdevopen(USART_send, NULL);
	stdin = fdevopen(NULL, USART_receive);

	init_int0();
	sei(); /// Enable global interrupt

	DDRD |= (1 << DDD5) | (1 << DDD6);
	PORTD |= (1 << PD5);
	PORTD &= ~(1 << PD6);

	while (1) {
		ADCSRA |= (1 << ADSC);
		while(bit_is_set(ADCSRA, ADSC)){
			;
		}
		float AngleMoving = ADC; // read angle to move from A0 (using potentiometer)
		AngleMoving = Map(AngleMoving, 0, 63, 0, 359); // Mapping potentiometer voltage reading to angle value. Motor will go to that angle position

		if (flag == 1){
			moveMotor(AngleMoving);
			printf("Angle Move: %.2f  ; Motor position: %.2f\n", AngleMoving, angle); // printing command position and final position
		}
	}
}
