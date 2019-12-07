#ifndef EXECUTION_H
#define EXECUTION_H

/**
 * Functions to execute, and track the execution of, a
 * Synacor program that has been loaded into the memory
 * of the VM.
 */

typedef enum {
    ExecutionSuccess,
    ExecutionInvalidInstructionError,
    ExecutionMemoryAccessError,
    ExecutionAllocError,
    ExecutionStackError,
    ExecutionDivisionByZeroError
} ExecutionStatus;

/**
 * Used to track execution of a program.
 */
typedef struct {
    unsigned short address;
    bool is_running;
    ExecutionStatus status;
} Execution;

/**
 * Set error status in the Execution and instruct it
 * to halt.
 */
void set_error(Execution *e, ExecutionStatus status);

/**
 * Executes program starting at address 0 in memory.
 *
 * Assumes that VM storage has been initialized. The
 * stack must first be allocated, memory & registers must
 * be set to 0.
 *
 * @return ExecutionSuccess if program runs to completion
 *         successfully, otherwise some error.
 */
ExecutionStatus execute_program();

#endif
