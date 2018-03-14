// Header for shared variables and other arrays that need to be accessed by
// multiple state machines.

#ifndef COMMON_H
#define COMMON_H

#include <string.h>

#include "drivers/storage.h"

// Addresses for next open file info and data blocks.
uint8_t next_file_info_addr = 0x00;
uint8_t next_file_data_addr = 0x00;

// Cached list of files and memory indexes.
char file_list[MAX_FILES][MAX_FILENAME_LENGTH];
uint8_t file_addr_indexes[MAX_FILES][2];
uint8_t num_files = 0;

// Locks for performing reading and writing.
uint8_t write_flag = 0x00;
uint8_t read_flag = 0x00;

// File information section.
char command_name[2];
char write_fname[MAX_FILENAME_LENGTH];
char write_string[MAX_FILE_SIZE];

// Reading data section.
uint8_t read_start_addr = 0x00;
uint8_t read_offset = 0x00;

// Character display buffer.
char disp_buffer[MAX_FILE_SIZE + 1];

// Boot flags.
uint8_t boot_complete = 0x00;
uint8_t metadata_building = 0x00;

// Command entered flag.
uint8_t command_flag = 0x00;

// Functions:

// Updates RAM cached file metadata arrays.
void update_metadata_cache(uint8_t len) {
    strcpy(file_list[num_files], write_fname);
    
    file_addr_indexes[num_files][0] = next_file_data_addr;
    next_file_data_addr += len; // Increment location for next string writes.
    file_addr_indexes[num_files][1] = next_file_data_addr - 1;

    // Increment location for file info.
    next_file_info_addr += 8;

    num_files++;
}

// Appends new character to display buffer.
void write_disp_buffer(char * c) {
    strncpy(&disp_buffer[strlen(disp_buffer)], c, 1);
}

#endif