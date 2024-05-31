/*
 * buzzer.c
 *
 * Created: 5/19/2024 9:00:47 PM
 *  Author: keep_
 */ 

#include <avr/interrupt.h>
#include <stdio.h>

#include "buzzer.h"
#include "ultrasonic.h"
#include "potentiometer.h"
#include "serial.h"

int overall_cycles = 100;
int volume = 0;
int count = 0;
char buffer[16];
uint16_t frequency = 0;

void init_buzzer(){
	DDRB |= (1 << BUZZER_PIN);
	TCCR0A = (1 << WGM01); //CTC
	TCCR0B = (1 << CS02); //Prescaler: 256
	OCR0A = 100;
}

void buzz(uint16_t distance){
	frequency = (int)(distance * (MAX_FREQUENCY-MIN_FREQUENCY) / (MAX_DETECT_DISTANCE) + MIN_FREQUENCY);
	overall_cycles = F_CPU / (frequency * BUZZER_PRESCALER);
	volume = read_potentiometer();
	OCR0A = overall_cycles * volume / 1024;
	TIMSK0 |= (1 << OCIE0A);
}

bool is_buzzing(){
	return count > 0;
}

ISR(TIMER0_COMPA_vect){
	if (OCR0A == overall_cycles * volume / 1024){
		PORTB &= ~(1 << BUZZER_PIN);
		OCR0A = overall_cycles * (1024 - volume) / 1024;
	} else {
		PORTB |= (1 << BUZZER_PIN);
		OCR0A = overall_cycles * volume / 1024;
	}
	count++;
	if (count > frequency){
		count = 0;
		TIMSK0 &= ~(1 << OCIE0A);
	}
}