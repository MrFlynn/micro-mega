#include "../common.h"

// Removes a file and it's contents from RAM cache as well as EEPROM.
void rm_command() {
    uint8_t idx = search(write_fname);
    
    if (idx == 255) {
        return;
    } else {
        // Set remove flag.
        rm_flag = 0x01;

        // Set addresses to remove.
        read_start_addr = file_addr_indexes[idx][0];
        read_offset = file_addr_indexes[idx][1] - read_start_addr;
        metadata_rm_address = 0x02 + (idx * 10);

        // Remove file from RAM cache.
        memset(file_list[idx], 0, sizeof(file_list[idx]));
        file_addr_indexes[idx][0] = 0; file_addr_indexes[idx][1] = 1;
        num_files--;

        // Enable write flag.
        write_flag = 0x01;
    }
}