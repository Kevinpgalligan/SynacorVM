#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef enum {
    StackOpSuccess,
    StackOverflowError,
    StackNoElementsError
} StackOpStatusCode;

typedef struct {
    size_t num_elements;
    size_t capacity;
    unsigned short *elements;
} Stack;

Stack *stack_init();
void stack_free(Stack *stack);
StackOpStatusCode stack_push(Stack *stack, unsigned short value);
StackOpStatusCode stack_pop(Stack *stack, unsigned short *value);

#endif
