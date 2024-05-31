/*
 * serial.c
 *
 * Created: 5/19/2024 10:11:01 PM
 *  Author: keep_
 */ 

#include <avr/io.h>
#include "serial.h"

void init_serial(){
	UBRR0H = 0;
	UBRR0L = 103; // 9600 baud rate
	UCSR0B |= (1 << TXEN0); //enable transmit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); //8 Bits
}

void send_serial(char* data){
	for (uint8_t i = 0; data[i]; i++) {
		while (!(UCSR0A & (1 << UDRE0))); //Data Register Empty.
		UDR0 = data[i];
	}
}