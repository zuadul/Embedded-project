/*
 * main.c
 *
 *  Created on: Jul 31, 2019
 *      Author: marof
 */

#include <avr/io.h>
#include<util/delay.h>
#include<stdbool.h>
#include<stdio.h>

int8_t stage = 1; /**< 0 means calling stage ,1 means music stage.*/
int8_t led_state;
#define led PC2
/**
 * @brief Increase the volume.
 *
 *@details This function does work for volume up.For testing purpose it will blink LED1.
 */

void volume_up() {
	printf("volume_up");

	if((PIND&(1<<PD1))>>PD1){ //pull up button
			PORTD &=~(1<<PD1);


		}
		else{
			PORTD |= (1<<PD1);
			_delay_ms(2000);

		}
}


void volume_down() {
	printf("volume_down");

	if((PIND&(1<<PD2))>>PD2){ //pull up button
				PORTD &=~(1<<PD2);


			}
			else{
				PORTD |= (1<<PD2);
				_delay_ms(2000);

			}
}


void answer_call() {
	printf("answer_call");

	if((PIND&(1<<PD0))>>PD0){ //pull up button
				PORTD &=~(1<<PD0);


			}
			else{
				PORTD |= (1<<PD0);
				_delay_ms(2000);

			}
}

void reject_call() {

	if((PIND&(1<<PD0))>>PD0){ //pull up button
				PORTD &=~(1<<PD0);


			}
			else{
				PORTD |= (1<<PD0);
				_delay_ms(2000);

			}
}


void next_song() {

	if((PIND&(1<<PD4))>>PD4){ //pull up button
				PORTD &=~(1<<PD4);


			}
			else{
				PORTD |= (1<<PD4);
				_delay_ms(2000);

			}
}


void previous_song() {

	if((PIND&(1<<PD3))>>PD3){ //pull up button
				PORTD &=~(1<<PD3);


			}
			else{
				PORTD |= (1<<PD3);
				_delay_ms(2000);

			}
}


void play_song() {
	printf("play_song");

	if((PIND&(1<<PD0))>>PD0){ //pull up button
				PORTD &=~(1<<PD0);


			}
			else{
				PORTD |= (1<<PD0);
				_delay_ms(2000);

			}
}


void pause_song() {
	printf("pause_song");

	if((PIND&(1<<PD0))>>PD0){ //pull up button
				PORTD &=~(1<<PD0);


			}
			else{
				PORTD |= (1<<PD0);
				_delay_ms(2000);

			}

}
void voice_dial(){

}
void redial(){

}


void call() {
	while (1) {
		if (stage)
			break;
		if (bit_is_set(PINB, PIN0)) {
			while (bit_is_set(PINB, PIN0))
				;
			_delay_ms(500);
			if (bit_is_set(PINB, PIN0)) {
				while (bit_is_set(PINB, PIN0))
					;
				reject_call();
			}

			else{
				answer_call();
				if(bit_is_set(PINB,PIN3)&&bit_is_set(PINB,PIN0) ){
					voice_dial();
				}
				if(bit_is_set(PINB,PIN0))
				{
					_delay_ms(500);
					if(bit_is_set(PINB,PIN0))
						redial();
				}
			}

		}
	}
}


void music() {
	bool playing = true;
	while (1) {
		if (!stage)
			break;
		if (bit_is_set(PINB, PB0)) {
			while (bit_is_set(PINB, PB0))
				;
			if (playing) {
				pause_song();
				playing = false;
			} else {
				play_song();
			}
		}

		if (bit_is_set(PINB, PB1))
			volume_up();

		if (bit_is_set(PINB, PB2))
			volume_down();

		if (bit_is_set(PINB, PB3)) {
			while (bit_is_set(PINB, PIN3))
				;
			previous_song();
		}

		if (bit_is_set(PINB, PIN4)) {
			while (bit_is_set(PINB, PB4))
				;
			next_song();
		}

	}
}
void connected()
{
	while(1){
		PORTC ^= (1<<led);
		_delay_ms(100);
		PORTC ^= (1<<led);
		_delay_ms(100);
		PORTC ^= (1<<led);
		_delay_ms(100);
		PORTC ^=(1<<led);
		_delay_ms(7000);

	}
}

void disconnected()
{
	while(1){
		PORTC ^= (1<<led);
			_delay_ms(100);
			PORTC ^= (1<<led);
			_delay_ms(100);
			PORTC ^= (1<<led);
			_delay_ms(100);
			PORTC ^=(1<<led);
			_delay_ms(2000);

		}
}
void pairing()
{
	while(1){
		PORTC ^= (1<<led);
		_delay_ms(500);
	}
}
void talking()
{
	while(1){
		PORTC ^= (1<<led);
		_delay_ms(7000);
	}
}
void music_play()
{
	while(1){
		PORTC ^= (1<<led);
			_delay_ms(10000);
		}
}
void bettary_low()
{
	while(1){
		PORTC ^= (1<<led);
			_delay_ms(1000);
		}
}

void charging()
{
	PORTC |= (1<<led);
}

void charging_complete()
{
	PORTC &= ~(1<<led);
}
void blink_led(){
	while(1){
		switch(led_state){
		case 0:
			connected();
			break;
		case 1:
			disconnected();
			break;
		case 2:
			pairing();
			break;
		case 3:
			talking();
			break;

		case 4:
			music_play();
			break;
		case 5:
			bettary_low();
			break;
		case 6:
			charging();
			break;

		case 7:
			charging_complete();
			break;
		}
	}
}


int main() {

	DDRB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4)); /// SET PORTB 0-4 AS INPUT.
		DDRD = ((1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3) | (1 << PD4)); /// SET PORTD 0-4 AS OUTPUT.
	while (1) {
		switch (stage) {
		case 0:
			call();
			break;
		case 1:
			music();
			break;
		default:
			break;
		}
	}
	return 0;
}
