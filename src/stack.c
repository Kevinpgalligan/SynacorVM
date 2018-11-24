#include "stack.h"

#include <stdlib.h>
#include <stdbool.h>

const size_t INITIAL_CAPACITY = 8;

Stack *stack_init() {
    Stack *stack = malloc(sizeof *stack);
    if (stack == NULL) {
        return NULL;
    }
    stack->num_elements = 0;
    stack->capacity = INITIAL_CAPACITY;
    stack->elements = malloc(INITIAL_CAPACITY * sizeof *(stack->elements));
    if (stack->elements == NULL) {
        free(stack);
        return NULL;
    }
    return stack;
}

void stack_free(Stack *stack) {
    free(stack->elements);
    free(stack);
}
