#include "write_sm.h"

// Main state machine for write operations. Takes a write_state and returns
// the next state in the code.
enum WRITE_STATES write_tick(enum WRITE_STATES state) {
    switch(state) { // Transitions
        case write_start:
            state = write_wait;
            break;
        case write_wait:
            // Transition to `write_queue_ops` when flag is enabled.
            state = write_flag == 0x01 ? write_queue_ops : write_wait;
            break;
        case write_queue_ops:
            state = write_run_ops;
            break;
        case write_run_ops:
            if (empty(&write_head, &write_tail)) {
                // If the queue is empty, go back to wait and reset flag.
                state = write_wait;
                write_flag = 0x00;
            } else {
                state = write_run_ops;
            }
            break;
        default:
            state = write_start;
            break;
    }

    switch(state) { // Actions
        case write_start: break;
        case write_wait: break;
        case write_queue_ops:
            // Add filename and file contents strings into messaging queue.
            queue_string_write(write_fname, 
                next_file_info_addr, 
                &write_head,
                &write_tail);
            queue_string_write(write_string,
                next_file_data_addr,
                &write_head,
                &write_tail);
            
            uint8_t string_length = strlen(write_string);

            // Increment location for next string writes.
            next_file_data_addr += string_length;

            // Increment location for file info.
            next_file_info_addr += 8;

            // Queue up writes to metadata block.
            queue_metadata_writes(&write_head, &write_tail, string_length);

            break;
        case write_run_ops:
            // Keep performing operations and popping them off the list.
            perform_storage_operation(&write_head, &write_tail);
            break;
        default: break;
    }

    return state;
}