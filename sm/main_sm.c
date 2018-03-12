#include "main_sm.h"

enum MAIN_STATES main_tick(enum MAIN_STATES state) {
    switch(state) { // Transitions
        case main_start:
            state = main_setup_cache;
            break;
        case main_setup_cache:
            // Wait until the metadata SRAM cache has been built.
            state = boot_complete == 0x01 ? main_wait_command : main_setup_cache;
            break;
        case main_wait_command:
            // If the command flag has been triggered, parse the string.
            if (command_flag == 0x01) {
                state = main_parse_command_string;
            } else {
                state = main_wait_command;
            }

            break;
        case main_parse_command_string:
            state = main_run_command;
            break;
        case main_run_command:
            state = main_wait_command;
            break;
        default:
            state = main_start;
            break;
    }

    switch(state) { // Actions
        case main_start:
            break;
        case main_setup_cache:
            build_metadata_cache();
            break;
        case main_wait_command:
            break;
        case main_parse_command_string:
            break_command_string();
            break;
        case main_run_command:
            break;
        default:
            break;
    }

    return state;
}