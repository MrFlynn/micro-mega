#include "storage.h"

// Given op_t, this function writes the character to the given address in the 
// operator node.
void write_char(op_t * operator) {
    uint8_t * addr_ptr = &operator->addr;
    eeprom_write_byte(addr_ptr, (uint8_t)operator->c);
}

// Takes op_t and triggers a read from memory at the location specified in
// the queue node. Once memory has been read, the applicable returnfunc is
// run with te value taken from memory.
void read_val(op_t * operator) {
    // Convert address into address pointer.
    const uint8_t * addr_ptr = &operator->addr;
    
    // Get character from read operation and run operator returnfunc.
    uint8_t ret = eeprom_read_byte(addr_ptr);
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

        // Pop the head from the queue.
        pop(head, tail);
    }
}

// Pushes individual chracter writes on to the queue in preparation for a write
// operation. This function assumes that the characters will be written to
// consecutive locations in memory.
void queue_string_write(char * string,
    uint8_t start_addr,
    op_t ** head,
    op_t ** tail) {

    for (uint8_t i = 0; i < strlen(string); i++) {
        // Allocate memory for new operation.
        op_t * new_write = malloc(sizeof(op_t));

        // Setup new write operation for the queue.
        new_write->op_num = 1;
        new_write->addr = start_addr + i;
        new_write->c = &string[i];
        new_write->returnfunc = &voidfunc;
        new_write->next = NULL;

        // Push on to the queue.
        push(head, tail, new_write);
    }
}

void queue_metadata_writes(op_t ** head, op_t ** tail, uint8_t string_len) {
    op_t * file_start_write = malloc(sizeof(op_t));
    file_start_write->op_num = 1;
    file_start_write->addr = next_file_info_addr + 1;
    file_start_write->c = (char *)(next_file_data_addr - string_len);
    file_start_write->returnfunc = &voidfunc;
    file_start_write->next = NULL;

    push(head, tail, file_start_write);

    op_t * file_end_write = malloc(sizeof(op_t));
    file_end_write->op_num = 1;
    file_end_write->addr = next_file_info_addr + 1;
    file_end_write->c = (char *)next_file_data_addr;
    file_end_write->returnfunc = &voidfunc;
    file_end_write->next = NULL;

    push(head, tail, file_end_write);

    next_file_info_addr +=3;

    op_t * new_info_start = malloc(sizeof(op_t));
    new_info_start->op_num = 1;
    new_info_start->addr = NEXT_FILE_INFO_ADDR;
    new_info_start->c = (char *)next_file_info_addr;
    new_info_start->returnfunc = &voidfunc;
    new_info_start->next = NULL;

    push(head, tail, new_info_start);

    op_t * new_data_start = malloc(sizeof(op_t));
    new_data_start->op_num = 1;
    new_data_start->addr = NEXT_FILE_BYTE_ADDR;
    new_data_start->c = (char *)next_file_data_addr;
    new_data_start->returnfunc = &voidfunc;
    new_data_start->next = NULL;

    push(head, tail, new_info_start);
}