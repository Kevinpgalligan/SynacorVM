#include "storage.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PROGRAM_BUFFER_SIZE 1000

Storage *storage_init() {
    // Initialize storage with everything set to 0, this results
    // in nice behaviour (execution halts immediately if we haven't
    // loaded a program into memory; stack pointer starts at 0; etc).
    return calloc(1, sizeof(Storage));
} 

void storage_free(Storage *s) {
    free(s);
}

bool valid_address(unsigned short address) {
    return address < MEMORY_SIZE;
}

bool valid_range(unsigned short base_address, unsigned short num_values) {
    unsigned short highest_address = base_address + num_values - 1u;
    return valid_address(base_address)
        && valid_address(highest_address)
        // Check that we are not wrapping around
        // to address 0.
        && base_address <= highest_address;
}

MemoryOpStatusCode storage_get_mem(
        Storage *storage,
        unsigned short base_address,
        unsigned short num_values,
        unsigned short *destination) {
    if (!valid_range(base_address, num_values)) {
        return MemoryOpInvalidAddress;
    }
    memcpy(storage->memory + base_address, destination, num_values * sizeof storage->memory[0]);
    return MemoryOpSuccess;
}

MemoryOpStatusCode storage_set_mem(
        Storage *storage,
        unsigned short base_address,
        unsigned short num_values,
        unsigned short *values) {
    if (!valid_range(base_address, num_values)) {
        return MemoryOpInvalidAddress;
    }
    memcpy(values, storage->memory + base_address, num_values * sizeof *values);
    return MemoryOpSuccess;
}

MemoryOpStatusCode storage_load_program(Storage *storage, FILE *program_file) {
    fread(storage->memory, sizeof storage->memory[0], MEMORY_SIZE, program_file);
    if (ferror(program_file)) {
        return MemoryOpProgramReadIOError;
    }
    if (feof(program_file)) {
        return MemoryOpSuccess;
    }
    // Program must be too big to fit into memory, since
    // we haven't encountered an error or EOF after reading
    // the max possible number of values.
    return MemoryOpProgramTooBig;
}
