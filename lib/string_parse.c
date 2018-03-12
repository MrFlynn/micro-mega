#include "string_parse.h"

// Clears the three chracter buffers used by the break_command_string.
void clear_buffers() {
    memset(command_name, 0, sizeof(command_name));
    memset(write_fname, 0, sizeof(write_fname));
    memset(write_string, 0, sizeof(write_string));
}

// Turns diplay buffer into three distinct lists: one which contains the 
// command, one that has the filename, and one that contains the string
// to be written to the file (where relevant).
void break_command_string() {
    static uint8_t array_index;

    clear_buffers(); // Clear buffers used here.

    for(uint8_t i = 0; i < strlen(disp_buffer); i++) {
        char * ci = (char *)disp_buffer[i];

        if (*ci == ' ') {
            array_index++;
        } else {
            switch(array_index) {
                case 0:
                    strcat(command_name, ci);
                    break;
                case 1:
                    strcat(write_fname, ci);
                    break;
                case 2:
                    strcat(write_string, ci);
                    break;
                default:
                    break;
            }
        }
    }
}