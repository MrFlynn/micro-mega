#include "../common.h"

void rm_command() {
    uint8_t idx = search(write_fname);
    
    if (idx == 255) {
        return;
    } else {
        memset(file_list[idx], 0, sizeof(file_list[idx]));
    }
}