#ifndef COMMAND_H
#define COMMAND_H

#include <string.h>
#include "../common.h"
#include "../lib/string_parse.c"

#include "wf.c"
#include "rf.c"
#include "ls.c"

char wf_command_str[3] = "wf";
char rf_command_str[3] = "rf";
char rm_command_str[3] = "rm";
char ls_command_str[3] = "ls";

void run_command() {
    if (strcmp(command_name, wf_command_str) == 0) {
        wf_command();
    } else if (strcmp(command_name, rf_command_str) == 0) {
        rf_command();
    } else if (strcmp(command_name, rm_command_str) == 0) {
        return;
    } else if (strcmp(command_name, ls_command_str) == 0) {
        ls_command();
    }
}

#endif