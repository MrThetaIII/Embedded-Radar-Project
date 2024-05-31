/*
 * potentiometer.h
 *
 * Created: 5/20/2024 2:30:29 AM
 *  Author: keep_
 */ 


#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_

#include <avr/io.h>

#define MAX_VOLTAGE 5
#define MIN_VOLTAGE 0
#define POTENTIOMETER_PIN PC0

void init_potentiometer();
uint16_t read_potentiometer();

#endif /* POTENTIOMETER_H_ */