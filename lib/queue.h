#ifndef QUEUE_H
#define QUEUE_H

typedef struct operation {
    uint8_t op_num;             // Memory operation; 0: read, 1: write.
    uint8_t addr;               // Address to perform operation on.
    char * c;                   // Character to write (optional).
    void (*returnfunc)(char *); // Return function (optional).
    struct operation * next;    // Next operation in the queue.
} op_t;

void push(op_t ** head, op_t ** tail, struct operation * next_node);
void pop(op_t ** head, op_t ** tail);
uint8_t empty(op_t ** head, op_t ** tail);
void voidfunc(char * c);

#endif