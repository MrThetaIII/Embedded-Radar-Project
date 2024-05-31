/*
 * ultrasonic.c
 *
 * Created: 5/19/2024 9:00:09 PM
 *  Author: keep_
 */ 

#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>

#include "ultrasonic.h"
#include "serial.h"
#include "buzzer.h"
#include "lcd.h"
#include "servo.h"

#define F_CPU 16000000UL

#include <util/delay.h>

volatile uint16_t distance = 0;
char buffer[16];

void init_ultrasonic(){
	DDRB |= (1 << ULTRASONIC_TRIGGER_PIN);
	DDRB &= ~(1 << ULTRASONIC_ECHO_PIN);
	PORTB &= ~(1 << ULTRASONIC_TRIGGER_PIN);
	
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC, 1024 Prescaler
	OCR1A = (F_CPU / ULTRASONIC_TIMER_PRESCALER) * (TRIGGER_INTERVAL / 1000.0);
	TIMSK1 |= (1 << OCIE1A);
}

void trigger_ultrasonic() {
	PORTB |= (1 << ULTRASONIC_TRIGGER_PIN);
	_delay_us(10);
	PORTB &= ~(1 << ULTRASONIC_TRIGGER_PIN);
}

uint16_t read_ultrasonic() {
	uint16_t duration;
	while (!(PINB & (1 << ULTRASONIC_ECHO_PIN)));
	TCNT1 = 0;
	while (PINB & (1 << ULTRASONIC_ECHO_PIN));
	duration = TCNT1;
	return (uint16_t)((duration / 2) * SOUND_SPEED * ((float)ULTRASONIC_TIMER_PRESCALER / F_CPU));
}

ISR(TIMER1_COMPA_vect) {
	trigger_ultrasonic();
	_delay_us(10);
	distance = read_ultrasonic();
	if (distance <= MAX_DETECT_DISTANCE) {
		lcd_command(LCD_CLEAR);
		lcd_command(LCD_HOME);
		snprintf(buffer, 16, "distance:%u\n", distance);
		send_serial(buffer);
		snprintf(buffer, 16, "Distance: %u ", distance);
		lcd_print(buffer);
		lcd_goto(1,0);
		snprintf(buffer, 16, "Angle: %u", get_servo_angle());
		lcd_print(buffer);
		if (!is_buzzing()){
			buzz(distance);
		}
	}
}