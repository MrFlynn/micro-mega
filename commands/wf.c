#include "../common.h"

// Sets write flag to enable write state machine to write file data to EEPROM.
// Also clears the display.
void wf_command() {
    write_flag = 0x01;
    memset(disp_buffer, 0, sizeof(disp_buffer));
}