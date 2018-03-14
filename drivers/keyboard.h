#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#include "../common.h"

#define DATAPORT PIND & 0x02       // Data bus.
#define VECTORPORT INT0_vect       // Interrupt vector port.

uint8_t count = 11;                // Number of bits to receive for each key.

// Function definitions.
void KB_init();
void KB_destroy();
void decode_and_push(uint8_t input);

// Lookup tables.
const uint8_t scancodes[38] = {
    0x1C, 0x32, 0x21, 0x23, 0x24, 0x2B, 0x34, 0x33, 0x43, 0x3B, 0x42, 0x4B,
    0x3A, 0x31, 0x44, 0x4D, 0x15, 0x2D, 0x1B, 0x2C, 0x3C, 0x2A, 0x1D, 0x22, 
    0x35, 0x1A, 0x45, 0x16, 0x1E, 0x26, 0x25, 0x2E, 0x36, 0x3D, 0x3E, 0x46,
    0x29, 0x49
};

const char char_lookup[38]  = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', ' ', '.'
};

#endif