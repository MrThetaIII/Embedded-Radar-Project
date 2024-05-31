/*
 * serial.h
 *
 * Created: 5/19/2024 10:10:47 PM
 *  Author: keep_
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

void init_serial();
void send_serial(char* data);
uint16_t get_servo_angle();

#endif /* SERIAL_H_ */