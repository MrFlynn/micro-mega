#ifndef STORAGE_C
#define STORAGE_C

#include "storage.h"

// Given op_t, this function writes the character to the given address in the 
// operator node.
void write_char(op_t * operator) {
    eeprom_write_byte((uint8_t *)operator->addr, operator->c);
}

// Takes op_t and triggers a read from memory at the location specified in
// the queue node. Once memory has been read, the applicable returnfunc is
// run with te value taken from memory.
void read_val(op_t * operator) {
    // Get character from read operation and run operator returnfunc.
    uint8_t ret = eeprom_read_byte((uint8_t *)operator->addr);
    operator->returnfunc((char *)&ret);
}

// Takes head and tail for messaging queue and performs the operation 
// specified by the head of the queue. Then it removes the message from the
// queue.
//
// Operations will only be performed if the EEPROM is ready.
void perform_storage_operation(op_t ** head, op_t ** tail) {
    if (eeprom_is_ready() == 1) {
        // Only run if the EEPROM is ready for reading or writing.
        switch((*head)->op_num) {
            case 0:
                // Operation 0 is a read.
                read_val(*head);
                break;
            case 1:
                // Operation 1 is a write.
                write_char(*head);
                break;
            default: break;
        }        
        
        // Pop the head from the queue.
        pop(head, tail);
    }
}

// Pushes individual character writes on to the queue in preparation for a write
// operation. This function assumes that the characters will be written to
// consecutive locations in memory.
void queue_string_write(char * string,
    uint8_t start_addr,
    op_t ** head,
    op_t ** tail) {

    for (uint8_t i = 0; i < strlen(string); i++) {
        // Create new messaging queue node.
        op_t * new_write = new_op_t(1, start_addr + i, string[i], &voidfunc);

        // Push on to the queue.
        push(head, tail, new_write);
    }
}

// Given a starting address and an offset in addition to the head and tail of a
// queue, this function generates individual read operations and pushes them
// on the queue.
void read_in_range(uint8_t addr_start, 
    uint8_t addr_offset, 
    op_t ** head,
    op_t ** tail) {

    for (uint8_t i = 0; i < addr_offset; i++) {
        op_t * new_read = new_op_t(0, addr_start + i, '0', &write_disp_buffer);
        push(head, tail, new_read);
    }
}

// This function enqueues operations to update information in the metadata 
// section of memory for files.
void queue_metadata_writes(op_t ** head, op_t ** tail, uint8_t string_len) {
    // Queue write in file metadata block for starting address of file contents
    op_t * file_start_write = new_op_t(1, (next_file_info_addr), 
                                        (next_file_data_addr - string_len), 
                                        &voidfunc);    
    // Queue write in file metadata block for ending address of file contents.
    op_t * file_end_write = new_op_t(1, (next_file_info_addr + 1), 
                                        next_file_data_addr, 
                                        &voidfunc);
    // Update address for next empty byte of metadata memory.
    op_t * new_info_start = new_op_t(1, NEXT_FILE_INFO_ADDR, 
                                        (next_file_info_addr + 3), 
                                        &voidfunc);
    // Update address for next byte of free file content memory.
    op_t * new_data_start = new_op_t(1, NEXT_FILE_BYTE_ADDR, 
                                        next_file_data_addr, 
                                        &voidfunc);
    
    // Push everything on to the queue.
    push(head, tail, file_start_write);
    push(head, tail, file_end_write);
    push(head, tail, new_info_start);
    push(head, tail, new_data_start);
    
    next_file_info_addr +=3;
}

// Extracts file metadata from EEPROM and places it into RAM for faster access
// of file metadata.
void build_metadata_cache() {
    // Continue only if EEPROM is ready.
    if (eeprom_is_ready() == 1 && metadata_building == 0x00) {
        // Block size and temporary storage array.
        uint8_t block_size = (MAX_FILES * 10) + 2;
        uint8_t file_metadata[block_size];
        metadata_building = 0x01;

        // Read data from memory.
        eeprom_read_block((void *)file_metadata, 
            (const void *)NEXT_FILE_INFO_ADDR,
            block_size);

        // Wait until operation has completed.
        eeprom_busy_wait();

        // Get next available byte addresses.
        next_file_info_addr = file_metadata[0] != 0xFF ? file_metadata[0] : FILE_INFO_START;
        next_file_data_addr = file_metadata[1] != 0xFF ? file_metadata[1] : FILE_REGION_START;

        for (uint8_t i = 2; i < block_size; i++) {
            uint8_t curr_byte = file_metadata[i];

            if (curr_byte != 0xFF) {
                // Discard if cell has empty data.
                if (i % 11 == 10) {
                    // Starting address of file i.
                    file_addr_indexes[num_files][0] = curr_byte;
                } else if (i % 11 == 0) {
                    // Ending address of file i.
                    file_addr_indexes[num_files][1] = curr_byte;
                    num_files++;
                } else {
                    // Copy title character to file list cache.
                    strncpy(&file_list[num_files][strlen(file_list[num_files])],
                        &(char)curr_byte, 1);
                }
            }
        }

        // Set boot complete flags.
        boot_complete = 0x01;
        metadata_building = 0x00;
    }
}

#endif