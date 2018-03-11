#ifndef MAIN_SM
#define MAIN_SM

#include "../common.h"

typedef enum MAIN_STATES {
    main_start,
    main_setup_cache,
    main_send_data,
} main_state;

#endif