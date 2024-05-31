/*
 * ultrasonic.h
 *
 * Created: 5/19/2024 9:02:32 PM
 *  Author: keep_
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include <avr/io.h>

#define F_CPU 16000000UL
#define MAX_DETECT_DISTANCE 50 //cm
#define SOUND_SPEED 34300 // cm/s

#define ULTRASONIC_ECHO_PIN PB4
#define ULTRASONIC_TRIGGER_PIN PB5

#define ULTRASONIC_TIMER_PRESCALER 1024
#define TRIGGER_INTERVAL 200 //ms

void init_ultrasonic();

#endif /* ULTRASONIC_H_ */