#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define DATAPORT (~PIND & 0x02)    // Data bus.
#define VECTORPORT INT0_vect       // Interrupt vector port.

// Current character returned by the keyboard.
volatile uint8_t curr_char_code = 0x00;

// Function definitions.
void KB_init();
void KB_destroy();

#endif
