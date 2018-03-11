#include "read_sm.h"

enum READ_STATES read_tick(enum READ_STATES state) {
    switch(state) { // Transitions
        case read_start:
            state = read_wait;
            break;
        case read_wait:
            // Go to next state if the flag to read is set.
            state = read_flag == 0x01 ? read_queue_ops : read_wait;
            break;
        case read_queue_ops:
            state = read_run_ops;
            break;
        case read_run_ops:
            // Reset flag and go back to wait if read queue is empty.
            if (empty(&read_head, &read_tail)) {
                state = read_wait;
                read_flag = 0x00;
            } else {
                state = read_run_ops;
            }

            break;
        default:
            state = read_start;
            break;
    }

    switch(state) { // Actions
        case read_start: break;
        case read_wait: break;
        case read_queue_ops:
            // Queue data read operations.
            read_in_range(read_start_addr, read_offset, &read_head, &read_tail);
            break;
        case write_run_ops:
            // Continuously perform operations until queue is empty.
            perform_storage_operation(&read_head, &read_tail);
            break;
        default:
            break;
    }

    return state;
}