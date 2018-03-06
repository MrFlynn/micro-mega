#ifndef STORAGE_H
#define STORAGE_H

#include <avr/eeprom.h>

// Max number of files to store and the max filename length.
#define MAX_FILES 16
#define MAX_FILENAME_LENGTH 8

/*
 * Region to store filenames and starting and ending addresses.
 * File information consists of 8 bytes for the filename, 1 byte for the 
 * starting address, and 1 byte for the ending address. 
 */
#define FILE_INFO_START 0x0004
#define FILE_INFO_END   0x0504

/*
 * Holds addresses for next file info block and next place file data can be
 * stored.
 */
#define NEXT_FILE_INFO_ADDR 0x0000
#define NEXT_FILE_BYTE_ADDR 0x5005

// Region for storing bytes of information for each file.
#define FILE_REGION_START   0x0505
#define FILE_REGION_END     0x8000 // 4KB max size.

// Functions:
void write_char(uint8_t addr, char c);
char read_val(uint8_t addr);

#endif