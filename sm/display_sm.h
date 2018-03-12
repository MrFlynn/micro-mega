#ifndef DISPLAY_SM
#define DISPLAY_SM

#include <string.h>
#include "../common.h"
#include "../drivers/display.c"

typedef enum DISPLAY_STATES {
    display_start,
    display_refresh
} display_state;

#endif