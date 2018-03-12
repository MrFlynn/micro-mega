#include "../common.h"

void rf_command() {
    uint8_t idx = search(write_fname);
    read_start_addr = file_addr_indexes[i][0];
    read_offset = file_addr_indexes[i][1] - read_start_addr;

    read_flag = 0x01;
}