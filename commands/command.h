#ifndef COMMAND_H
#define COMMAND_H

#include <string.h>
#include "../common.h"
#include "../lib/string_parse.c"

#include "ls.c"
#include "wf.c"

void run_command() {
    if (strcmp(command_name, "wf")) {
        wf_command();
    } else if (strcmp(command_name, "rf")) {
        rf_command();
    } else if (strcmp(command_name, "rm")) {
        return;
    } else if (strcmp(command_name, "ls")) {
        ls_command();
    }
}

#endif