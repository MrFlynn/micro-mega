#include <string.h>
#include "../common.h"

// Lists all filenames located in EEPROM.
//
// This function employs a small shortcut in that the filenames are read from
// the RAM cache and not from EEPROM. This speeds up things significantly.
void ls_command() {
    if (metadata_building == 0x01) {
        return;
    }

    for (uint8_t i = 0; i < num_files; i++) {
        // Copy the filename preceeded by a space.
        strncpy(&disp_buffer[strlen(disp_buffer)], space, 1);
        strncpy(&disp_buffer[strlen(disp_buffer)], file_list[i], strlen(file_list[i]));
    }
}