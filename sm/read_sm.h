#ifndef READ_SM
#define READ_SM

#include <string.h>

#include "../common.h"
#include "../lib/queue.h"
#include "../drivers/storage.c"

typedef enum READ_STATES {
    read_start,
    read_wait,
    read_queue_ops,
    read_run_ops
} read_state;

op_t * read_head = NULL;
op_t * read_tail = NULL;

#endif