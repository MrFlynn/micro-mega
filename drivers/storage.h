#ifndef STORAGE_H
#define STORAGE_H

#include <avr/eeprom.h>
#include <string.h>
#include "../common.h"
#include "../lib/queue.c"

// Max number of files to store and the max filename length.
#define MAX_FILES 16
#define MAX_FILE_SIZE 32
#define MAX_FILENAME_LENGTH 8

// Holds addresses for next file info block and next place file data can be
// stored.
#define NEXT_FILE_INFO_ADDR 0x0000
#define NEXT_FILE_BYTE_ADDR 0x0001

// Region to store filenames and starting and ending addresses.
// File information consists of 8 bytes for the filename, 1 byte for the 
// starting address, and 1 byte for the ending address. This area is also
// referred to as the metadata block.
#define FILE_INFO_START 0x0002
#define FILE_INFO_END   0x00A2

// Region for storing the actual file contents.
#define FILE_REGION_START 0x00A3
#define FILE_REGION_END   0x0FA0 // 4K max number of addresses.

// Functions:
void write_char(op_t * operator);
void read_val(op_t * operator);
void perform_storage_operation(op_t ** head, op_t ** tail);
void queue_string_write(char * string, 
    uint8_t start_addr, 
    op_t ** head, 
    op_t ** tail);
void read_in_range(uint8_t addr_start, 
    uint8_t addr_offset,
    op_t ** head,
    op_t ** tail);
void queue_metadata_writes(op_t ** head, op_t ** tail, uint8_t string_len);
void build_metadata_cache();
void remove_area(uint8_t addr_start, 
    uint8_t addr_offset,
    op_t ** head,
    op_t ** tail);

#endif