#include "display_sm.h"

enum DISPLAY_STATES display_tick(enum DISPLAY_STATES state) {
    switch(state) { // Transitions
        case display_start:
            state = display_refresh;
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
            LCD_init();
            break;
        case display_refresh:
            const char * disp_string = &disp_buffer;
            LCD_DisplayString(1, disp_string);
            break;
        default:
            break;
    }
    
    return state;
}