#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

#define motor_DDR DDRD
#define motor_PORT PORTD

#define left_motor_A PD2
#define left_motor_B PD3
#define left_motor_EN PD4

#define right_motor_A PD5
#define right_motor_B PD6
#define right_motor_EN PD7

#define diamiter 7
#define PI 3

init_motor()
{
	motor_DDR |= (1<<left_motor_A)|(1<<left_motor_B)|(1<<left_motor_EN);
	motor_DDR |= (1<<right_motor_A)|(1<<right_motor_B)|(1<<right_motor_EN);
}

void motor_clockwise(uint8_t A,uint8_t B){
	motor_PORT |= (1<<A);
	motor_PORT &= ~(1<<B);
}

void motor_counter_clockwise(uint8_t A,uint8_t B){
	motor_PORT |= (1<<B);
	motor_PORT &=~(1<<A);
}

void motor_stop(uint8_t motor_EN){
	motor_PORT &= ~(1<<motor_EN);
}

void motor_start(uint8_t motor_EN){
	motor_PORT |= (1<<motor_EN);
}


int main()
{
	init_motor();
	motor_stop(left_motor_EN);
	motor_stop(right_motor_EN);
	while(1){
		motor_clockwise(left_motor_A,left_motor_B);
	motor_clockwise(right_motor_A,right_motor_B);

        motor_enable(left_motor_EN);
		motor_enable(right_motor_EN);
         _delay_ms(1000);
		motor_stop(left_motor_EN);
			motor_stop(right_motor_EN);
	}
}
