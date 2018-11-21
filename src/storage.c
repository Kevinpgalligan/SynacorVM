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

StorageOpStatusCode storage_get_mem(
        Storage *storage,
        unsigned short base_address,
        unsigned short num_values,
        unsigned short *destination) {
    if (!valid_range(base_address, num_values)) {
        return StorageOpInvalidAddress;
    }
    memcpy(destination, storage->memory + base_address, num_values * sizeof storage->memory[0]);
    return StorageOpSuccess;
}

StorageOpStatusCode storage_set_mem(
        Storage *storage,
        unsigned short base_address,
        unsigned short num_values,
        unsigned short *values) {
    if (!valid_range(base_address, num_values)) {
        return StorageOpInvalidAddress;
    }
    memcpy(storage->memory + base_address, values, num_values * sizeof *values);
    return StorageOpSuccess;
}

StorageOpStatusCode storage_load_program(Storage *storage, FILE *program_file) {
    fread(storage->memory, sizeof storage->memory[0], MEMORY_SIZE, program_file);
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

void storage_set_reg(Storage *s, unsigned short register_code, unsigned short value) {
    s->registers[register_code - REGISTER_OFFSET] = value;
}

unsigned short storage_get_reg_or_num(Storage *s, unsigned short code) {
    if (is_register(code)) {
        return s->registers[code - REGISTER_OFFSET];
    }
    return code % MAX_NUM;
}
