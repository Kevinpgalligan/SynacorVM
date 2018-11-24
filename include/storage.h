#ifndef STORAGE_H
#define STORAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stack.h>

// These values are fixed according to the spec of
// the Synacor VM. The address space is 2^15, and
// registers are referred to as if they're extra
// memory addresses at the end of the address space..
#define MEMORY_SIZE      32768
#define REGISTERS        8
#define REGISTER_OFFSET  MEMORY_SIZE
#define MAX_NUM          32768u

typedef enum {
    StorageOpInvalidAddress,
    StorageOpProgramReadIOError,
    StorageOpProgramTooBig,
    StorageOpSuccess
} StorageOpStatus;

/**
 * Sets the globally-used stack. This must be called before
 * any stack operations are executed.
 */
void set_stack(Stack *stack);

StackOpStatus stack_push(unsigned short value);
StackOpStatus stack_pop(unsigned short *value);

/**
 * Copy N values from memory starting from the provided address.
 *
 * @param base_address address at which to start the copy.
 * @param num_values number of memory cells to copy.
 * @param destination location where the copied values will be
 *        stored, should be at least num_values in size.
 * @return StorageOpInvalidAddress if the copy range is outside
 *         the range of valid memory addresses, otherwise
 *         StorageOpSuccess indicating that the copy was successful.
 */
StorageOpStatus get_mem(
    unsigned short base_address,
    unsigned short num_values,
    unsigned short *destination);

/**
 * Set the values of N cells in memory starting from the provided address.
 *
 * @param base_address address at which to start setting values.
 * @param num_values number of memory cells to set.
 * @param destination location where the values of the cells will be
 *        retrieved from, should be at least num_values in size.
 * @return StorageOpInvalidAddress if the memory range is outside
 *         the range of valid memory addresses, otherwise
 *         StorageOpSuccess indicating that the operation was successful.
 */
StorageOpStatus set_mem(
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
StorageOpStatus load_program(FILE *program_file);

void set_reg(unsigned short register_code, unsigned short value);
unsigned short reg_or_num(unsigned short code);
bool is_register(unsigned short address);

#endif
