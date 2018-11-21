#include "stack.h"

#include <stdlib.h>

const size_t INITIAL_CAPACITY = 8;
const size_t GROWTH_MULTIPLIER = 2;

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

StackOpStatusCode stack_push(Stack *stack, unsigned short value) {
    if (stack->num_elements == stack->capacity) {
        size_t new_capacity = GROWTH_MULTIPLIER * stack->capacity;
        stack->elements = realloc(stack->elements, new_capacity);
        if (stack->elements == NULL) {
            return StackOverflowError;
        }
        stack->capacity = new_capacity;
    }
    stack->elements[stack->num_elements++] = value;
    return StackOpSuccess;
}

StackOpStatusCode stack_pop(Stack *stack, unsigned short *value) {
    if (stack->num_elements == 0) {
        return StackNoElementsError;
    }
    stack->num_elements--;
    *value = stack->elements[stack->num_elements];
    return StackOpSuccess;
}
