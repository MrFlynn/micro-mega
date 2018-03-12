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
            LCD_ClearScreen();
            for (uint8_t i = 0; i < strlen(disp_buffer); i++) {
                LCD_WriteData((unsigned char)disp_buffer[i]);
            }

            break;
        default:
            break;
    }
    
    return state;
}