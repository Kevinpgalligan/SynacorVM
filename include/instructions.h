#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

/**
 * This header contains the definition of an instruction and
 * the mapping from code -> instruction.
 */

#include <stdlib.h>
#include "storage.h"
#include "execution.h"

/**
 * This type of function contains the logic of an instruction.
 */
typedef void (*InstructionFn)(Execution *e, unsigned short *args);

typedef struct {
    unsigned short code;
    const char *name;
    InstructionFn fn;
    size_t num_args;
} Instruction;

/**
 * Returns the Instruction associated with the given
 * code, if it exists. Otherwise, returns NULL.
 */
Instruction *lookup_instruction(unsigned short code);

#endif
