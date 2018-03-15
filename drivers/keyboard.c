#include "keyboard.h"

void KB_init() {
    sei();        // Enable global interrupt register.
    EIMSK = 0x01; // Enable INT0 (PD2) to receive external interrupts.
    EICRA = 0x02; // Set interrupts on falling edge.
}

void KB_destroy() {
    cli();         // Clears global interrupt register.
    EIMSK &= 0xFE; // Disable interrupts on INT0.
    EICRA &= 0xFD; // Disable falling-edge inteerupts.
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
    }
}

void decode_and_push(uint8_t input) {
    static uint8_t stop_repeat;
    
    if (input == 0x5A && strlen(disp_buffer) > 0) {
        // Intercept 'enter' key and set command flag.
        command_flag = 0x01;
        return;
    } else if (input == 0x66 && strlen(disp_buffer) > 0) {
        // Remove last character with backspace.
        disp_buffer[strlen(disp_buffer) - 1] = '\0';
    }

    for (uint8_t i = 0; i < 38; i++) {
        if (scancodes[i] == input) {
            if (strcmp(&char_lookup[i], &disp_buffer[strlen(disp_buffer)]) 
                && stop_repeat < 1) {
                // Prevent keyboard from sending duplicate keys.
                stop_repeat++;
                break;
            } else {
                // If scan code matches, append character to display buffer.
                strncpy(&disp_buffer[strlen(disp_buffer)], &char_lookup[i], 1);
                
                // Reset stop repeat counter to zero.
                stop_repeat = 0;
                break;
            }
        }
    }
}