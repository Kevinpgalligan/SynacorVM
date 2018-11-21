#include <stdlib.h>
#include "storage.h"
#include "execution.h"

typedef void (*InstructionFn)(Execution *e, Storage *s, unsigned short *args);

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
