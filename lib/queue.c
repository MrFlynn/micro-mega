#ifndef QUEUE_C
#define QUEUE_C

#include "queue.h"

// Creates new op_t using the given inputs. Allocates memory and sets all 
// internal variables. The next node is set to be NULL, therefor any functions
// that utilize the node returned by this function should set it accordingly.
op_t * new_op_t(uint8_t opnum, uint8_t address, char ic, void (*f)(char *)) {
    op_t * new_node = malloc(sizeof(op_t));
    
    new_node->op_num = opnum;
    new_node->addr = address;
    new_node->c = (uint8_t)ic;
    new_node->returnfunc = f;
    new_node->next = NULL;
    
    return new_node;
}

// Pushes new op_t to the queue. The function will also properly set the head 
// and tail pointers as required when performing a queue push.
void push(op_t ** head, op_t ** tail, op_t * next_node) {
    if (*head == NULL) {
        // If list is empty, set head and tail to next_node.
        *head = next_node;
        *tail = next_node;
    } else {
        // Append to last item and set new tail pointer.
        (*tail)->next = next_node;
        *tail = next_node;
    }
}

// Removes (pops) op_t from the front of the queue (if it exists). 
// 
// All memory operations are handled internally and pointers are set where
// applicable.
void pop(op_t ** head, op_t ** tail) {
    if (*head == NULL) {
        // Exit if list is empty.
        return;
    } else if (*head == *tail) {
        // Remove last item in the list. Free memory for head node and reset
        // pointers.
        free(*head);
        *head = NULL; 
        *tail = NULL;
    } else {
        // Get next item in list.
        op_t * new_next = (*head)->next;

        // Free memory for head and set to next item.
        free(*head);
        *head = new_next;
    }
}

// Returns a 1 if the head and tail pointer of the queue are equal, i.e. if 
// the queue has no items in it.
uint8_t empty(op_t ** head, op_t ** tail) {
    return (uint8_t)(*head == NULL && *tail == NULL);
}

// Empty function to pass into message queue if the response from the message
// requires no response.
void voidfunc(char * c) {
    return;
}

#endif