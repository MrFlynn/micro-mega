#include <string.h>
#include "../common.h"

void ls_command() {
    for (uint8_t i = 0; i < num_files; i++) {
        for (uint8_t j = 0; i < sizeof(file_list[i]); i++) {
            strncpy(&disp_buffer[strlen(disp_buffer)], &file_list[i][j], 1);
        }

        char * space = ' ';
        strncpy(&disp_buffer[strlen(disp_buffer)], space, 1);
    }
}