#include "display_sm.h"

enum DISPLAY_STATES display_tick(enum DISPLAY_STATES state) {
    const char * test = disp_buffer;
    
    switch(state) { // Transitions
        case display_start:
            state = display_refresh;
            break;
        case display_boot_message:
            state = boot_complete == 0x01 ? display_refresh : display_boot_message;
            break;
        case display_refresh:
            state = display_refresh;
            break;
        default:
            state = display_start;
            break;
    }

    switch(state) { // Actions
        case display_start:
            break;
        case display_boot_message:
            LCD_DisplayString(1, boot_message);
            break;
        case display_refresh:
            LCD_DisplayString(1, test);
            break;
        default:
            break;
    }
    
    return state;
}