/*
 * potentiometer.c
 *
 * Created: 5/20/2024 2:30:20 AM
 *  Author: keep_
 */ 

#include "potentiometer.h"

void init_potentiometer(){
	ADMUX = (1 << REFS1); // 5V, PC0
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable, 128 Prescaler
}

uint16_t read_potentiometer() {
	ADCSRA |= (1 << ADSC); // Start reading
	while (!(ADCSRA & (1 << ADIF))); // Wait till completed
	ADCSRA |= (1 << ADIF);
	
	return ADC;
}