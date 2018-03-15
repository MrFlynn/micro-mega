#ifndef MAIN_SM
#define MAIN_SM

#include "../common.h"
#include "../lib/string_parse.c"
#include "../drivers/storage.c"
#include "../commands/command.h"

typedef enum MAIN_STATES {
    main_start,
    main_setup_cache,
    main_wait_command,
    main_parse_command_string,
    main_run_command
} main_state;

#endif