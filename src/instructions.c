#include "instructions.h"
#include "storage.h"
#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define BINARY_OP(arg1, op, arg2) (reg_or_num(arg1) op reg_or_num(arg2))

#define INPUT_BUFFER_CAPACITY 1000

// Statically allocated buffer means that only a limited
// amount of input can be read from the keyboard. If the user
// inputs more characters than the size of the buffer, the input
// will be cut short and the snipped input might leak into the
// next read.
static char input_buffer[INPUT_BUFFER_CAPACITY];
static size_t input_buffer_size = 0;
static size_t input_buffer_index = 0;

static void read_line_into_input_buffer() {
    if (fgets(input_buffer, INPUT_BUFFER_CAPACITY, stdin) == NULL) {
        printf("ERROR: could not read input buffer.\n");
    } else {
        input_buffer_size = strlen(input_buffer);
        input_buffer_index = 0;
    }
}

static unsigned short read_input_char() {
    while (input_buffer_index >= input_buffer_size) {
        read_line_into_input_buffer();
    }
    return input_buffer[input_buffer_index++];
}

static void set_execution_address(Execution *execution, unsigned short code) {
    execution->address = reg_or_num(code);
}

static void boolean_set(unsigned short register_code, bool result) {
    unsigned short val = 0;
    if (result) {
        val = 1;
    }
    set_reg(register_code, val);
}
    
void halt(Execution *execution, unsigned short *args) {
    execution->is_running = false;
}

void set(Execution *execution, unsigned short *args) {
    set_reg(args[0], reg_or_num(args[1]));
}

void push(Execution *execution, unsigned short *args) {
    StackOpStatus status = stack_push(reg_or_num(args[0]));
    if (status != StackOpSuccess) {
        set_error(execution, ExecutionStackError);
    }
}

void pop(Execution *execution, unsigned short *args) {
    unsigned short value;
    StackOpStatus status = stack_pop(&value);
    if (status != StackOpSuccess) {
        set_error(execution, ExecutionStackError);
    }
    set_reg(args[0], value);
}

void eq(Execution *execution, unsigned short *args) {
    boolean_set(args[0], BINARY_OP(args[1], ==, args[2]));
}

void gt(Execution *execution, unsigned short *args) {
    boolean_set(args[0], BINARY_OP(args[1], >, args[2]));
}

void jmp(Execution *execution, unsigned short *args) {
    set_execution_address(execution, args[0]);
}

void jt(Execution *execution, unsigned short *args) {
    if (reg_or_num(args[0]) != 0) {
        set_execution_address(execution, args[1]);
    }
}

void jf(Execution *execution, unsigned short *args) {
    if (reg_or_num(args[0]) == 0) {
        set_execution_address(execution, args[1]);
    }
}

void add(Execution *execution, unsigned short *args) {
    set_reg(args[0], BINARY_OP(args[1], +, args[2]) % MAX_NUM);
}

void mult(Execution *execution, unsigned short *args) {
    set_reg(args[0], BINARY_OP(args[1], *, args[2]) % MAX_NUM);
}

void mod(Execution *execution, unsigned short *args) {
    set_reg(args[0], BINARY_OP(args[1], %, args[2]) % MAX_NUM);
}

void and(Execution *execution, unsigned short *args) {
    set_reg(args[0], BINARY_OP(args[1], &, args[2]));
}

void or(Execution *execution, unsigned short *args) {
    set_reg(args[0], BINARY_OP(args[1], |, args[2]));
}

void not(Execution *execution, unsigned short *args) {
    set_reg(args[0], ~reg_or_num(args[1]) % MAX_NUM);
}

void rmem(Execution *execution, unsigned short *args) {
    unsigned short value;
    StorageOpStatus status = get_mem(reg_or_num(args[1]), 1u, &value);
    if (status != StorageOpSuccess) {
        set_error(execution, ExecutionMemoryAccessError);
    } else {
        set_reg(args[0], value);
    }
}

void wmem(Execution *execution, unsigned short *args) {
    unsigned short value = reg_or_num(args[1]);
    StorageOpStatus status = set_mem(reg_or_num(args[0]), 1u, &value);
    if (status != StorageOpSuccess) {
        set_error(execution, ExecutionMemoryAccessError);
    }
}

void call(Execution *execution, unsigned short *args) {
    // Assumes that the execution address has already been
    // updated to point to next instruction.
    if (stack_push(execution->address) != StackOpSuccess) {
        set_error(execution, ExecutionStackError);
        return;
    }
    set_execution_address(execution, args[0]);
}

void ret(Execution *execution, unsigned short *args) {
    unsigned short return_address;
    StackOpStatus status = stack_pop(&return_address);
    if (status == StackEmpty) {
        execution->is_running = false;
        return;
    } else if (status != StackOpSuccess) {
        set_error(execution, ExecutionStackError);
        return;
    }
    set_execution_address(execution, return_address);
}

void out(Execution *execution, unsigned short *args) {
    printf("%c", (unsigned char) reg_or_num(args[0]));
}

void in(Execution *execution, unsigned short *args) {
    set_reg(args[0], read_input_char());
}

void noop(Execution *execution, unsigned short *args) {
    // Do nothing.
}

static Instruction instructions[] = {
    {  0, "halt", &halt, 0 },
    {  1,  "set",  &set, 2 },
    {  2, "push", &push, 1 },
    {  3,  "pop",  &pop, 1 },
    {  4,   "eq",   &eq, 3 },
    {  5,   "gt",   &gt, 3 },
    {  6,  "jmp",  &jmp, 1 },
    {  7,   "jt",   &jt, 2 },
    {  8,   "jf",   &jf, 2 },
    {  9,  "add",  &add, 3 },
    { 10, "mult", &mult, 3 },
    { 11,  "mod",  &mod, 3 },
    { 12,  "and",  &and, 3 },
    { 13,   "or",   &or, 3 },
    { 14,  "not",  &not, 2 },
    { 15, "rmem", &rmem, 2 },
    { 16, "wmem", &wmem, 2 },
    { 17, "call", &call, 1 },
    { 18,  "ret",  &ret, 0 },
    { 19,  "out",  &out, 1 },
    { 20,   "in",   &in, 1 },
    { 21, "noop", &noop, 0 }
};

static const size_t num_instructions = sizeof instructions / sizeof instructions[0];

Instruction *lookup_instruction(unsigned short code) {
    // This would be more efficient if the index of the
    // instructions in the array matched their instruction
    // code, we could return instructions[code] immediately.
    // But it's less flexible that way, can't leave some
    // instructions incomplete / can't "reserve" instruction
    // codes.
    for (size_t i = 0; i < num_instructions; i++) {
        if (instructions[i].code == code) {
            return &instructions[i];
        }
    }
    return NULL;
}
