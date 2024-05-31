/*
 * servo.h
 *
 * Created: 5/19/2024 9:02:57 PM
 *  Author: keep_
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#include <avr/io.h>

#define F_CPU 16000000UL
#define SERVO_SPEED 15 //deg/sec
#define SERVO_PIN PB3

void init_servo();
void set_servo_angle(uint16_t angle);
void toggle_servo_sweep();

#endif /* SERVO_H_ */