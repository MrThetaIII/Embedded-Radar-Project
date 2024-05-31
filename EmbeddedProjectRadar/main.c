/*
 * main.c
 *
 * Created: 5/19/2024 8:50:22 PM
 *  Author: keep_
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define F_CPU 16000000UL

#include <util/delay.h>
#include "servo.h"
#include "serial.h"
#include "ultrasonic.h"
#include "potentiometer.h"
#include "buzzer.h"
#include "lcd.h"

char buffer[16];

int main(void)
{
	init_serial();
	init_servo(); toggle_servo_sweep();
	init_ultrasonic(); 
	init_potentiometer();
	init_buzzer();
	lcd_init();
	
	
	sei();
    while(1);
}