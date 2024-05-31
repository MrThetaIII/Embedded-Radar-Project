/*
 * servo.c
 *
 * Created: 5/19/2024 8:59:46 PM
 *  Author: keep_
 */ 

#include <stdio.h>
#include <avr/interrupt.h>

#include "servo.h"
#include "serial.h"

float sweep_angle = 0;
float change = 0;
int count_changes = 0;
char buffer[16];

void init_servo() {
	DDRB |= (1 << SERVO_PIN); //Clear OC2A on compare match when up-counting. Set OC2A on compare match when down-counting.

	// Configure Timer 2 for Fast PWM mode
	TCCR2A = (1 << WGM21) | (1 << WGM20) | (1 << COM2A1);
	TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20); // 1024 prescaler, 60 Hz, 16.384 ms
	
	change = SERVO_SPEED * 0.016384;
	
	// Set initial servo position (e.g., 90 degrees)
	set_servo_angle(90);
}

void set_servo_angle(uint16_t angle) {
	uint16_t pwm_value = (int)(7 + angle * 32 / 180); // 0 to 180 degrees

	// Update OCR2A register to set servo position
	OCR2A = pwm_value;
}

uint16_t get_servo_angle(){
	return (OCR2A - 7) * 180 / 32;
}

void toggle_servo_sweep(){
	TIMSK2 |= (1<<TOIE2);
}

ISR(TIMER2_OVF_vect) {
	sweep_angle += change;
	if(sweep_angle >= 180 || sweep_angle <= 0) change *= -1;
	
	count_changes++;
	
	if (count_changes > 4){
		snprintf(buffer, 16, "angle:%u\n", (int)sweep_angle);
		send_serial(buffer);
		count_changes = 0;
	}
	
	set_servo_angle((int)sweep_angle);
}

