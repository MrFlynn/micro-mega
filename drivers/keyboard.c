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
    // Count and received character buffer.
    static uint8_t count;
    static uint8_t char_read_buffer;
  
    if (count > 0 && count < 9) {
        // Data on bits 1 to 8.
        // 0: start, 9: parity, 10: stop, 11: ACK.
        if (DATAPORT) {
            char_read_buffer |= (1 << count); // Shift data over by count and or with storage.
        }
    }

    count++;

    if (count >= 11) {
        // Set curr_char_code to value of char_byte after 8 clock cycles.
        curr_char_code = char_read_buffer;

        // Reset counter and char_read_buffer values.
        count = 0;
        char_read_buffer = 0x00;
    }
}