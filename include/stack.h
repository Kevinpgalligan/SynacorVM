#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * Stack utility class. Contains only memory-related functions,
 * manipulation of the VM's stack is done through storage.h.
 */

typedef enum {
    StackOpSuccess,
    StackOverflowError,
    StackEmpty
} StackOpStatus;

typedef struct {
    size_t num_elements;
    size_t capacity;
    unsigned short *elements;
} Stack;

Stack *stack_init();
void stack_free(Stack *stack);

#endif
