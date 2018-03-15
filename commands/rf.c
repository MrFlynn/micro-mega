#include "../common.h"

void rf_command() {
    uint8_t idx = search(write_fname);
    
    if (idx == 255) {
        return;
    } else {
        strncpy(&disp_buffer[strlen(disp_buffer)], space, 1);
        read_start_addr = file_addr_indexes[idx][0];
        read_offset = file_addr_indexes[idx][1] - read_start_addr;

        read_flag = 0x01;
    }    
}