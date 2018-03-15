#include "../common.h"

void wf_command() {
    write_flag = 0x01;
    memset(disp_buffer, 0, sizeof(disp_buffer));
    command_flag = 0x00;
}