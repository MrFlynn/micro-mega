#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "../common.h"

#define DATAPORT PIND & 0x02       // Data bus.
#define VECTORPORT INT0_vect       // Interrupt vector port.

// Function definitions.
void KB_init();
void KB_destroy();
void decode_and_push(uint8_t input);

char scancodes[38][2] PROGMEM = {
    0x1C, 'a', 0x32, 'b', 0x21, 'c', 0x23, 'd', 0x24, 'e', 0x2B, 'f', 0x34, 'g', 
    0x33, 'h', 0x43, 'i', 0x3B, 'j', 0x42, 'k', 0x4B, 'l', 0x3A, 'm', 0x31, 'n',
    0x44, 'o', 0x4D, 'p', 0x15, 'q', 0x2D, 'r', 0x1B, 's', 0x2C, 't', 0x3C, 'u',
    0x2A, 'v', 0x1D, 'w', 0x22, 'x', 0x35, 'y', 0x1A, 'z', 0x45, '0', 0x16, '1',
    0x1E, '2', 0x26, '3', 0x25, '4', 0x2E, '5', 0x36, '6', 0x3D, '7', 0x3E, '8',
    0x46, '9', 0x29, ' ', 0x49, '.'
};

#endif