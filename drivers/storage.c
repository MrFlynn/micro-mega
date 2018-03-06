#include "storage.h"

void write_char(uint8_t addr, char c) {
    // Writes char at given address.
    uint8_t *addr_ptr = addr; // Conversion between types.
    eeprom_write_byte(addr_ptr, c);
}

char read_val(uint8_t addr) {
    // Reads char from given address.
    const uint8_t *addr_ptr = addr; // Conversion between types.
    return eeprom_read_byte(addr_ptr);
}