#ifndef STORAGE_H
#define STORAGE_H

/**
 * This header includes all of the functions for manipulating
 * the VM's storage, including the registers, memory and stack.
 * Registers and memory are allocated statically. The stack
 * must be allocated at runtime through the set_stack(...)
 * function, which may fail.
 */

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

/**
 * Sets the globally-used stack. This must be called before
 * any stack operations are executed.
 */
void set_stack(Stack *stack);
StackOpStatus stack_push(unsigned short value);
StackOpStatus stack_pop(unsigned short *value);

typedef enum {
    StorageOpInvalidAddress,
    StorageOpProgramReadIOError,
    StorageOpProgramTooBig,
    StorageOpSuccess
} StorageOpStatus;

/**
 * Copy N values from memory starting from the provided address.
 *
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
 * @return StorageOpProgramReadIOError if there is an error when
 *         reading from the program input stream.
 *         StorageOpProgramTooBig if the program is too big to fit
 *         into memory of Storage.
 *         StorageOpSuccess if successful.
 */
StorageOpStatus load_program(FILE *program_file);

/**
 * Set the value of a register.
 */
void set_reg(unsigned short register_code, unsigned short value);

/**
 * Get a register value or a number.
 *
 * Assumes that 'code' is either a valid number or a register.
 *
 * @return the value of 'code', if its a valid number; otherwise,
 *         the value of the register represented by 'code'.
 */
unsigned short reg_or_num(unsigned short code);

/**
 * Determine whether an address is actually the code of a register.
 *
 * @return whether the address value represents a register.
 */
bool is_register(unsigned short address);

#endif
