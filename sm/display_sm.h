#ifndef DISPLAY_SM
#define DISPLAY_SM

#include <string.h>
#include "../common.h"
#include "../drivers/display.c"

const char * boot_message = "booting...";

enum DISPLAY_STATES {
    display_start,
    display_boot_message,
    display_refresh
} display_state;

#endif