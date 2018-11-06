#ifndef STORAGE_H
#define STORAGE_H

#include <stdlib.h>
#include <stdio.h>

// These values are fixed according to the spec of
// the Synacor VM.
// 2^15 address space.
#define MEMORY_SIZE 32768
#define REGISTERS 8

typedef enum {
    MemoryOpInvalidAddress,
    MemoryOpProgramReadIOError,
    MemoryOpProgramTooBig,
    MemoryOpSuccess
} MemoryOpStatusCode;

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

/**
 * Free up memory that was allocated to a Storage struct.
 */
void storage_free(Storage *s);

/**
 * Copy N values from memory starting from the provided address.
 *
 * @param s the target storage.
 * @param base_address address at which to start the copy.
 * @param num_values number of memory cells to copy.
 * @param destination location where the copied values will be
 *        stored, should be at least num_values in size.
 * @return MemoryOpInvalidAddress if the copy range is outside
 *         the range of valid memory addresses, otherwise
 *         MemoryOpSuccess indicating that the copy was successful.
 */
MemoryOpStatusCode storage_get_mem(
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
 * @return MemoryOpInvalidAddress if the memory range is outside
 *         the range of valid memory addresses, otherwise
 *         MemoryOpSuccess indicating that the operation was successful.
 */
MemoryOpStatusCode storage_set_mem(
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
 * @return MemoryOpProgramReadIOError if there is an error when
 *         reading from the program input stream.
 *         MemoryOpProgramTooBig if the program is too big to fit
 *         into memory of Storage.
 *         MemoryOpSuccess if successful.
 */
MemoryOpStatusCode storage_load_program(Storage *s, FILE *program_file);

#endif
