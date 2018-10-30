#ifndef STORAGE_H
#define STORAGE_H

#include <stdlib.h>
#include <stdio.h>

// 2^15 address space.
#define MEMORY_SIZE 32768

// Registers are represented by numbers in the range 32768..32775
// TODO: should these be exposed in header?
#define REGISTER_OFFSET 32768
#define REGISTERS 8

typedef enum {
    MemoryOpInvalidAddress,
    MemoryOpProgramReadIOError,
    MemoryOpProgramTooBig,
    MemoryOpSuccess
} MemoryOpStatusCode;

typedef struct {
    unsigned short memory[MEMORY_SIZE];
    unsigned short registers[REGISTERS];
} Storage;

Storage *storage_init();
void storage_free(Storage *s);

MemoryOpStatusCode storage_get_mem(
    Storage *s,
    unsigned short base_address,
    unsigned short num_values,
    unsigned short *destination);

MemoryOpStatusCode storage_set_mem(
    Storage *s,
    unsigned short base_address,
    unsigned short num_values,
    unsigned short *values);

MemoryOpStatusCode storage_load_program(Storage *s, FILE *program_file);

#endif
