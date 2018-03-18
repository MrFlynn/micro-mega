#include "../common.h"

const char * command_list = "commamds: wf, ls, rf, rm"

// Appends above string to display buffer.
void help_command() {
    strncpy(&disp_buffer[strlen(disp_buffer)], command_list, strlen(command_list));
}