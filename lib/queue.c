#include "queue.h"

void push(op_t ** tail, op_t ** head, op_t * next_node) {
    if (*head == NULL) {
        *head = next_node;
        *tail = next_node;
    } else {
        (*tail)->next = next_node;
        *tail = next_node;
    }
}

void pop(op_t ** head, op_t ** tail) {
    if (*head == NULL) {
        return;
    } else if (*head == *tail) {
        (*head)->returnfunc((*head)->c);
        free(*head);
        *head = NULL; 
        *tail = NULL;
    } else {
        (*head)->returnfunc((*head)->c);
        op_t * new_next = (*head)->next;

        free(*head);
        *head = new_next;
    }
}