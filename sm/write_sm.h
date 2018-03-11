#ifndef WRITE_SM
#define WRITE_SM

#include <string.h>

#include "../common.h"
#include "../lib/queue.h"
#include "../drivers/storage.c"

typedef enum WRITE_STATES { 
    write_start, 
    write_wait,  
    write_queue_ops, 
    write_run_ops 
} write_state;

op_t * write_head = NULL;
op_t * write_tail = NULL;

#endif