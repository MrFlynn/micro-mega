#include "../common.h"

// Gets the index in memory for the file you want to read and triggers the read
// state machine.
void rf_command() {
    uint8_t idx = search(write_fname);
    
    if (idx == 255) {
        return;
    } else {
        strncpy(&disp_buffer[strlen(disp_buffer)], space, 1);

        // Set the starting address and the offset.
        read_start_addr = file_addr_indexes[idx][0];
        read_offset = file_addr_indexes[idx][1] - read_start_addr;

        read_flag = 0x01;
    }    
}