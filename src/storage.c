#include "storage.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const size_t STACK_GROWTH_MULTIPLIER = 2;

static unsigned short memory[MEMORY_SIZE];
static unsigned short registers[REGISTERS];
static Stack *stack;

void set_stack(Stack *allocated_stack) {
    stack = allocated_stack;
}

StackOpStatus stack_push(unsigned short value) {
    if (stack->num_elements == stack->capacity) {
        size_t new_capacity = STACK_GROWTH_MULTIPLIER * stack->capacity;
        stack->elements = realloc(stack->elements, new_capacity * sizeof *(stack->elements));
        if (stack->elements == NULL) {
            return StackOverflowError;
        }
        stack->capacity = new_capacity;
    }
    stack->elements[stack->num_elements++] = value;
    return StackOpSuccess;
}

StackOpStatus stack_pop(unsigned short *value) {
    if (stack->num_elements == 0) {
        return StackEmpty;
    }
    stack->num_elements--;
    *value = stack->elements[stack->num_elements];
    return StackOpSuccess;
}

static bool valid_address(unsigned short address) {
    return address < MEMORY_SIZE;
}

static bool valid_range(unsigned short base_address, unsigned short num_values) {
    unsigned short highest_address = base_address + num_values - 1u;
    return valid_address(base_address)
        && valid_address(highest_address)
        // Check that we are not wrapping around
        // to address 0.
        && base_address <= highest_address;
}

StorageOpStatus get_mem(
        unsigned short base_address,
        unsigned short num_values,
        unsigned short *destination) {
    if (!valid_range(base_address, num_values)) {
        return StorageOpInvalidAddress;
    }
    memcpy(destination, memory + base_address, num_values * sizeof memory[0]);
    return StorageOpSuccess;
}

StorageOpStatus set_mem(
        unsigned short base_address,
        unsigned short num_values,
        unsigned short *values) {
    if (!valid_range(base_address, num_values)) {
        return StorageOpInvalidAddress;
    }
    memcpy(memory + base_address, values, num_values * sizeof *values);
    return StorageOpSuccess;
}

StorageOpStatus load_program(FILE *program_file) {
    fread(memory, sizeof memory[0], MEMORY_SIZE, program_file);
    if (ferror(program_file)) {
        return StorageOpProgramReadIOError;
    }
    if (feof(program_file)) {
        return StorageOpSuccess;
    }
    // Program must be too big to fit into memory, since
    // we haven't encountered an error or EOF after reading
    // the max possible number of values.
    return StorageOpProgramTooBig;
}

bool is_register(unsigned short address) {
    return REGISTER_OFFSET <= address && address < REGISTER_OFFSET + REGISTERS;
}

void set_reg(unsigned short register_code, unsigned short value) {
    registers[register_code - REGISTER_OFFSET] = value;
}

unsigned short reg_or_num(unsigned short code) {
    if (is_register(code)) {
        return registers[code - REGISTER_OFFSET];
    }
    return code % MAX_NUM;
}
