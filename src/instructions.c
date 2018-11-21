#include "instructions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define GET_MEM_OR_FAIL(pointer_name, address)\
    unsigned short *pointer_name = malloc(sizeof *pointer_name);\
    if (pointer_name == NULL) {\
        return InstructionAllocError;\
    }\
    if (storage_get_value(s, address, pointer_name) != StorageOpSuccess) {\
        return InstructionStorageAccessError;\
    }

void boolean_set(Storage *s, unsigned short register_code, bool result) {
    unsigned short val = 0;
    if (result) {
        val = 1;
    }
    storage_set_reg(s, register_code, val);
}
    
void halt(Execution *e, Storage *s, unsigned short *args) {
    e->is_running = false;
}

void set(Execution *e, Storage *s, unsigned short *args) {
    storage_set_reg(
        s,
        args[0],
        storage_get_reg_or_num(s, args[1]));
}

void eq(Execution *e, Storage *s, unsigned short *args) {
    boolean_set(
        s,
        args[0],
        storage_get_reg_or_num(s, args[1]) == storage_get_reg_or_num(s, args[2]));
}

void gt(Execution *e, Storage *s, unsigned short *args) {
    boolean_set(
        s,
        args[0],
        storage_get_reg_or_num(s, args[1]) > storage_get_reg_or_num(s, args[2]));
}

void jmp(Execution *e, Storage *s, unsigned short *args) {
    e->address = storage_get_reg_or_num(s, args[0]);
}

void jt(Execution *e, Storage *s, unsigned short *args) {
    if (storage_get_reg_or_num(s, args[0]) != 0) {
        jmp(e, s, &args[1]);
    }
}

void jf(Execution *e, Storage *s, unsigned short *args) {
    if (storage_get_reg_or_num(s, args[0]) == 0) {
        jmp(e, s, &args[1]);
    }
}

void add(Execution *e, Storage *s, unsigned short *args) {
    storage_set_reg(
        s,
        args[0],
        (storage_get_reg_or_num(s, args[1]) + storage_get_reg_or_num(s, args[2])) % MAX_NUM);
}

void mult(Execution *e, Storage *s, unsigned short *args) {
    storage_set_reg(
        s,
        args[0],
        (storage_get_reg_or_num(s, args[1]) * storage_get_reg_or_num(s, args[2])) % MAX_NUM);
}

void mod(Execution *e, Storage *s, unsigned short *args) {
    storage_set_reg(
        s,
        args[0],
        (storage_get_reg_or_num(s, args[1]) % storage_get_reg_or_num(s, args[2])) % MAX_NUM);
}

void and(Execution *e, Storage *s, unsigned short *args) {
    storage_set_reg(
        s,
        args[0],
        storage_get_reg_or_num(s, args[1]) & storage_get_reg_or_num(s, args[2]));
}

void or(Execution *e, Storage *s, unsigned short *args) {
    storage_set_reg(
        s,
        args[0],
        storage_get_reg_or_num(s, args[1]) | storage_get_reg_or_num(s, args[2]));
}

void not(Execution *e, Storage *s, unsigned short *args) {
    storage_set_reg(
        s,
        args[0],
        ~storage_get_reg_or_num(s, args[1]) % MAX_NUM);
}

void out(Execution *e, Storage *s, unsigned short *args) {
    printf("%c", (char) args[0]);
}

void noop(Execution *e, Storage *s, unsigned short *args) {
    // Do nothing.
}

Instruction instructions[] = {
    {  0, "halt", &halt, 0 },
    {  1,  "set",  &set, 2 },
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
    { 19,  "out",  &out, 1 },
    { 21, "noop", &noop, 1 }
};

const size_t num_instructions = sizeof instructions / sizeof instructions[0];

Instruction *lookup_instruction(unsigned short code) {
    for (size_t i = 0; i < num_instructions; i++) {
        if (instructions[i].code == code) {
            return &instructions[i];
        }
    }
    return NULL;
}
