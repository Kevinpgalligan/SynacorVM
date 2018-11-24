#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * Stack data structure. This header contains only memory management
 * functions, manipulation of the VM's stack is done through functions
 * in storage.h.
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

/**
 * Allocates memory for a stack and sets its attributes to their
 * initial values.
 *
 * @return NULL if allocation fails, otherwise pointer to stack.
 */
Stack *stack_init();

/**
 * Frees all allocations associated with the stack.
 */
void stack_free(Stack *stack);

#endif
