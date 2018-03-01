#ifndef DISPLAY_H
#define DISPLAY_H

#include <avr/io.h>

#define DATALINES PORTA

// Set specific bits on PORTC according to their port usage.
#define RW(m) (PORTC |= m & 0x01)
#define REGSELECT(r) (PORTC |= (r & 0x01) << 1)
#define CHIPSELECT(s) (PORTC |= (c & 0x02) << 2)
#define RESET(c) (PORTC |= (c & 0x01) << 4)

// Functions to interact with display.
void Display_Send_Command(uint8_t cmd);
void Display_Write_Data(unsigned char ch);
void Display_Reset();
void Display_Init();

#endif