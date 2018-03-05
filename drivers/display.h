#ifndef DISPLAY_H
#define DISPLAY_H

#include <avr/io.h>

#define DATALINES PORTA

// Set specific bits on PORTC according to their port usage.
#define RW(m) (PORTC |= m & 0x01) // C0
#define REGSELECT(r) (PORTC |= (r & 0x01) << 1) // C1
#define CHIPSELECT(s) (PORTC |= (s & 0x02) << 2) // C2, C3
#define RESET(c) (PORTC |= (c & 0x01) << 4) // C4
#define OPENABLE(e) (PORTC |= (e & 0x01) << 5) // C5

// Functions to interact with display.
void Display_Send_Command(uint8_t cmd);
void Display_Write_Data(unsigned char ch);
void Display_Reset();
void Display_Init();

#endif