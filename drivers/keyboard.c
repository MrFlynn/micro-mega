#include "keyboard.h"

void KB_init() {
    sei();        // Enable global interrupt register.
    EIMSK = 0x01; // Enable INT0 (PD2) to receive external interrupts.
}

void KB_destroy() {
    cli();         // Clears global interrupt register.
    EIMSK &= 0xFE; // Disable interrupts on INT0.
}

ISR(VECTORPORT) {
    // Received character buffer.
    static uint8_t char_read_buffer;
  
    if (count < 11 && count > 2) {
        // Data on bits 10 to 3.
        // 11: start, 2: parity, 1: stop, 0: ACK.
        char_read_buffer = char_read_buffer >> 1;
        if (DATAPORT) {
            char_read_buffer |= 0x80;
        }
    }

    count--;

    if (count == 0) {
        // Decode and add to display buffer.
        decode_and_push(char_read_buffer);

        // Reset counter and char_read_buffer values.
        count = 11;
        char_read_buffer = 0x00;
    }
}

void decode_and_push(uint8_t input) {
    if (input == 0x5A) {
        // Intercept 'enter' key and set command flag.
        command_flag = 0x01;
        return;
    }

    for (uint8_t i = 0; i < 38; i++) {
        if (scancodes[i][0] == input) {
            // If scancode matches, append character to display buffer.
            strcat(disp_buffer, scancodes[i][1]);
            return;
        }
    }
}