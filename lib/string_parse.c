#ifndef STRING_PARSE_C
#define STRING_PARSE_C

#include "string_parse.h"

// Clears the three character buffers used by the break_command_string.
void clear_buffers() {
    memset(command_name, 0, sizeof(command_name));
    memset(write_fname, 0, sizeof(write_fname));
    memset(write_string, 0, sizeof(write_string));
}

// Turns display buffer into three distinct lists: one which contains the 
// command, one that has the filename, and one that contains the string
// to be written to the file (where relevant).
void break_command_string() {
    uint8_t split1, split2 = 0x00;

    clear_buffers(); // Clear buffers used here.
    
    // Attemp to locate the first two spaces in display buffer.
    for (uint8_t i = 0; i < strlen(disp_buffer); i++) {
        if (disp_buffer[i] == ' ') {
            if (split1 == 0) {
                split1 = i;
            } else if (split2 == 0) {
                split2 = i;
                break;
            }
        }
    }
    
    // For commands with no or one argument (ls, rm, rf).
    if (split1 == 0) {
        strncpy(command_name, &disp_buffer[0], 2);
    } else {
        strncpy(command_name, &disp_buffer[0], split1);
    }
    
    // For commands with two arguments (wf).
    if (split2 == 0) {
        strncpy(write_fname, &disp_buffer[split1 + 1], 
            strlen(disp_buffer) - split1 - 1);
    } else {
        strncpy(write_fname, &disp_buffer[split1 + 1], split2 - split1 - 1);
        strncpy(write_string, &disp_buffer[split2 + 1], 
            strlen(disp_buffer) - split2 -1);
    }
}

// Searches through the file list array for a file with a matching name and 
// returns it's index. Default return value is 255 (chosen because file list
// array is much less than that).
uint8_t search(char s[]) {
    for (uint8_t i = 0; i < num_files; i++) {
        if (strcmp(file_list[i], s) == 0) {
            return i;
        }
    }

    return 255;
}

#endif