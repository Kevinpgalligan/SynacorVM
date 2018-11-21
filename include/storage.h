#ifndef STORAGE_H
#define STORAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// These values are fixed according to the spec of
// the Synacor VM. The address space is 2^15, and
// registers are referred to as if they're extra
// memory addresses at the end of the address space..
#define MEMORY_SIZE      32768
#define REGISTERS        8
#define REGISTER_OFFSET  MEMORY_SIZE
#define MAX_NUM          MEMORY_SIZE

typedef enum {
    StorageOpInvalidAddress,
    StorageOpProgramReadIOError,
    StorageOpProgramTooBig,
    StorageOpSuccess
} StorageOpStatusCode;

/**
 * Represents all storage of the VM, including memory,
 * registers and the stack.
 */
typedef struct {
    unsigned short memory[MEMORY_SIZE];
    unsigned short registers[REGISTERS];
} Storage;

/**
 * Allocate memory for and initialize a Storage struct.
 *
 * @return NULL if failed to allocate memory, otherwise pointer to Storage.
 */
Storage *storage_init();

void storage_free(Storage *s);

/**
 * Copy N values from memory starting from the provided address.
 *
 * @param s the target storage.
 * @param base_address address at which to start the copy.
 * @param num_values number of memory cells to copy.
 * @param destination location where the copied values will be
 *        stored, should be at least num_values in size.
 * @return StorageOpInvalidAddress if the copy range is outside
 *         the range of valid memory addresses, otherwise
 *         StorageOpSuccess indicating that the copy was successful.
 */
StorageOpStatusCode storage_get_mem(
    Storage *s,
    unsigned short base_address,
    unsigned short num_values,
    unsigned short *destination);

/**
 * Set the values of N cells in memory starting from the provided address.
 *
 * @param s the target storage.
 * @param base_address address at which to start setting values.
 * @param num_values number of memory cells to set.
 * @param destination location where the values of the cells will be
 *        retrieved from, should be at least num_values in size.
 * @return StorageOpInvalidAddress if the memory range is outside
 *         the range of valid memory addresses, otherwise
 *         StorageOpSuccess indicating that the operation was successful.
 */
StorageOpStatusCode storage_set_mem(
    Storage *s,
    unsigned short base_address,
    unsigned short num_values,
    unsigned short *values);

/**
 * Load a program from a binary file into memory at address 0.
 *
 * @param s the target Storage.
 * @param program_file input stream for the binary file containing
 *        the program.
 * @return StorageOpProgramReadIOError if there is an error when
 *         reading from the program input stream.
 *         StorageOpProgramTooBig if the program is too big to fit
 *         into memory of Storage.
 *         StorageOpSuccess if successful.
 */
StorageOpStatusCode storage_load_program(Storage *s, FILE *program_file);

void storage_set_reg(Storage *s, unsigned short register_code, unsigned short value);
unsigned short storage_get_reg_or_num(Storage *s, unsigned short code);
bool is_register(unsigned short address);

#endif
