#include "lcd.h"

static void lcd_pulse_enable(void) {
	LCD_CONTROL_PORT |= (1 << LCD_E);
	_delay_us(1); // Enable pulse width > 450ns
	LCD_CONTROL_PORT &= ~(1 << LCD_E);
	_delay_us(100); // Command execution time
}

void lcd_init(void) {
	// Set control pins as output
	LCD_CONTROL_DDR |= (1 << LCD_E) | (1 << LCD_RW) | (1 << LCD_RS);
	// Set data pins as output
	LCD_DATA_DDR = LCD_DATA_MASK;
	// Set additional data pin (PC4) as output
	DDRC |= (1 << LCD_DATA_DDR_PC4);
	// Initialize data ports to 0
	LCD_DATA_PORT &= ~LCD_DATA_MASK;
	PORTC &= ~(1 << LCD_DATA_PC4);

	_delay_ms(50); // Wait for more than 40ms after VCC rises to 2.7V

	// Function set: 8-bit, 2 line, 5x8 dots
	lcd_command(0x30);
	_delay_ms(5); // Wait for more than 4.1ms

	lcd_command(0x30);
	_delay_us(100); // Wait for more than 100us

	lcd_command(0x30);
	_delay_us(100);

	lcd_command(LCD_FUNCTION_SET);
	_delay_us(100);

	// Display on/off control: display on, cursor off, blinking off
	lcd_command(LCD_DISPLAY_ON);
	_delay_us(100);

	// Clear display
	lcd_command(LCD_CLEAR);
	_delay_ms(2); // Wait for more than 1.52ms

	// Entry mode set: increment automatically, no display shift
	lcd_command(LCD_ENTRY_MODE_SET);
	_delay_us(100);
}

static void lcd_write(uint8_t value, uint8_t rs) {
	if (value & (1 << 1)) {
		PORTC |= (1 << LCD_DATA_PC4);
		} else {
		PORTC &= ~(1 << LCD_DATA_PC4);
	}

	// Write remaining bits to PORTD
	LCD_DATA_PORT = (LCD_DATA_PORT & ~LCD_DATA_MASK) | ((value & 0x01) | (value & 0xFC));

	if (rs) {
		LCD_CONTROL_PORT |= (1 << LCD_RS); // RS = 1 for data
		} else {
		LCD_CONTROL_PORT &= ~(1 << LCD_RS); // RS = 0 for command
	}
	LCD_CONTROL_PORT &= ~(1 << LCD_RW); // RW = 0 for write

	lcd_pulse_enable(); // Pulse the enable pin
}

void lcd_command(uint8_t cmd) {
	lcd_write(cmd, 0);
}

void lcd_data(uint8_t data) {
	lcd_write(data, 1);
}

void lcd_print(const char *str) {
	while (*str) {
		lcd_data(*str++);
	}
}

void lcd_goto(uint8_t row, uint8_t col) {
	uint8_t address;
	switch (row) {
		case 0:
		address = 0x00 + col;
		break;
		case 1:
		address = 0x40 + col;
		break;
		default:
		return; // Invalid row, do nothing
	}
	lcd_command(0x80 | address); // Set DDRAM address
}
