// Header for shared variables and other arrays that need to be accessed by
// multiple state machines.

#ifndef COMMON_H
#define COMMON_H

#include "drivers/storage.h"

// Addresses for next open file info and data blocks.
uint8_t next_file_info_addr = 0x00;
uint8_t next_file_data_addr = 0x00;

// Cached list of files and memory indexes.
const char * file_list[MAX_FILES];
uint8_t file_addr_indexes[MAX_FILES][2];
uint8_t num_files = 0x00;

// Locks for performing reading and writing.
uint8_t write_flag = 0x00;
uint8_t read_flag = 0x00;

// Data to write section.
char * write_fname[MAX_FILENAME_LENGTH];
char * write_string[MAX_FILE_SIZE];

#endif