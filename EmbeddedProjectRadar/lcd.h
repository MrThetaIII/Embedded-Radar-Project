#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

// Define LCD control pins
#define LCD_E   PC1
#define LCD_RW  PC2
#define LCD_RS  PC3

// Define LCD data port
#define LCD_DATA_PORT PORTD
#define LCD_DATA_DDR  DDRD

// Define LCD data port mask for PD0-PD7 except PD1 (now PC4)
#define LCD_DATA_MASK ((1 << PD0) | (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7))

// Define additional data pin
#define LCD_DATA_PC4 PORTC4
#define LCD_DATA_DDR_PC4 PC4

// Define LCD control port
#define LCD_CONTROL_PORT PORTC
#define LCD_CONTROL_DDR  DDRC

// LCD command macros
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_ENTRY_MODE_SET 0x06
#define LCD_DISPLAY_ON 0x0C
#define LCD_FUNCTION_SET 0x38

// Function prototypes
void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_print(const char *str);
void lcd_goto(uint8_t row, uint8_t col);

#endif
