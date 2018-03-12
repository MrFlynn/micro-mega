#ifndef STRING_PARSE_H
#define STRING_PARSE_H

#include <string.h>
#include "../common.h"
#include "../drivers/storage.h"

void clear_buffers();
void break_command_string();
uint8_t search(char s[]);

#endif