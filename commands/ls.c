#include <string.h>
#include "../common.h"

void ls_command() {
    if (metadata_building == 0x01) {
        return;
    }

    for (uint8_t i = 0; i < num_files; i++) {
        strncpy(&disp_buffer[strlen(disp_buffer)], space, 1);
        strncpy(&disp_buffer[strlen(disp_buffer)], file_list[i], strlen(file_list[i]));
    }
}