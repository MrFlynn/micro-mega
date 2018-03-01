#include "keyboard.h"

void KB_init() {
    EICRA |= 0x02; // Set external interrupt register to falling-edge trigger.
    EIMSK |= 0x01; // Enable INT0 (PD2) to recieve external interrupts.
}

void KB_destroy() {
    EICRA &= 0xFD; // Turn off falling-edge triggering.
    EIMSK &= 0xFE; // Disable interrupts on INT0.
}

ISR(VECTORPORT) {
    // Count and character byte storage.
    static unsigned char count;
    static uint8_t char_byte;

    if (DATAPORT) {
        char_byte |= (1 << count);
    }

    count++;

    if (count > 7) {
        // Set curr_char_code to value of char_byte after 8 clock cycles.
        curr_char_code = char_byte;

        // Reset counter and char_byte values.
        count, char_byte = 0x00;
    }
}