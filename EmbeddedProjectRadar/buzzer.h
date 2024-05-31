/*
 * buzzer.h
 *
 * Created: 5/19/2024 9:02:41 PM
 *  Author: keep_
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include <avr/io.h>
#include <stdbool.h>

#define F_CPU 16000000UL
#define MAX_FREQUENCY 9000
#define MIN_FREQUENCY 300
#define BUZZER_PIN PB0
#define BUZZER_PRESCALER 256

void init_buzzer();
void buzz(uint16_t distance);
bool is_buzzing();

#endif /* BUZZER_H_ */