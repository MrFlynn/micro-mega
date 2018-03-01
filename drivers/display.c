#include "display.h"

void Display_Send_Command(uint8_t cmd) {
    REGSELECT(0); RW(0); // All commands have these signals as LOW.
    DATALINES = cmd;
}

void Display_Write_Data(unsigned char ch) {
    REGSELECT(1); RW(0); // Set display to write character.
    DATALINES = ch;
}

void Display_Reset() {
    RESET(1);
}

void Display_Init() {
    OPEANBLE(0x01);   // Enable display operations.
    CHIPSELECT(0x02); // Select the IC on the left side.

    Display_Send_Command(0x3F); // Turn display on.
    
    Display_Send_Command(0x41); // Set x=1, y=1, z=1.
    Display_Send_Command(0xB9);
    Display_Send_Command(0xC1);
}