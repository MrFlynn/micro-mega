#include <string.h>
#include "main_sm.h"

enum MAIN_STATES main_tick(enum MAIN_STATES state) {
    switch(state) { // Transitions
        case main_start:
            state = main_setup_cache;
            break;
        case main_setup_cache:
            state = main_send_data;
            break;
        case main_send_data:
            state = main_send_data;
            break;
        default:
            break;
    }

    switch(state) {
        case main_start:
            break;
        case main_setup_cache:
            next_file_info_addr = FILE_INFO_START;
            next_file_data_addr = FILE_REGION_START;

            strcpy(write_fname, "test");
            strcpy(write_string, "hello");

            write_flag = 0x01;

            break;
        case main_send_data:
            break;
        default:
            break;
    }

    return state;
}