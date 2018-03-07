#include "queue.h"

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

// Removes (pops) op_t from the front of the queue (if it exists). In addition,
// this function will run the specified `returnfunc` in the given queue node.
// 
// All memory operations are handled internally and pointers are set where
// applicable.
void pop(op_t ** head, op_t ** tail) {
    if (*head == NULL) {
        // Exit if list is empty.
        return;
    }

    // If the previous branch is false, execute returnfunc for head.
    (*head)->returnfunc((*head)->c);

    if (*head == *tail) {
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
    return (uint8_t)(*head == * tail);
}

// Empty function to pass into message queue if the response from the message
// requires no response.
void voidfunc(char * c) {
    return
}