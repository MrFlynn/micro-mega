#include <string.h>
#include "../common.h"

void ls_command() {
    for (uint8_t i = 0; i < num_files; i++) {
        for (uint8_t j = 0; i < sizeof(file_list[i]); i++) {
            strcat(disp_buffer, (char *)file_list[i][j]);
        }

        strcat(disp_buffer, " ");
    }
}