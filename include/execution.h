#ifndef EXECUTION_H
#define EXECUTION_H

typedef enum {
    ExecutionSuccess,
    ExecutionInvalidInstructionError,
    ExecutionMemoryAccessError,
    ExecutionAllocError,
    ExecutionStackError
} ExecutionStatus;

typedef struct {
    unsigned short address;
    bool is_running;
    ExecutionStatus status;
} Execution;

void set_error(Execution *e, ExecutionStatus status);

/**
 * Executes program starting at address 0 in memory.
 *
 * Assumes that VM storage has been initialized, i.e. the
 * stack must first be allocated.
 *
 * @return ExecutionSuccess if program runs to completion
 *         successfully, otherwise some error.
 */
ExecutionStatus execute_program();

#endif
