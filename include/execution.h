#ifndef EXECUTION_H
#define EXECUTION_H

#include "storage.h"
#include <stdbool.h>

// Create Execution on the stack with
// appropriate default values.
#define EXECUTION_INIT(name) Execution name = { 0, true, ExecutionSuccess }

typedef enum {
    ExecutionSuccess,
    ExecutionInvalidInstructionError,
    ExecutionMemoryAccessError,
    ExecutionAllocError,
    ExecutionInstructionError
} ExecutionStatusCode;

ExecutionStatusCode execute(Storage *s);

typedef struct {
    unsigned short address;
    bool is_running;
    ExecutionStatusCode status;
} Execution;

#endif
