#include "storage.h"
#include "execution.h"
#include <bool.h>
#include <stdio.h>

/**
 * TODO:
 *  - check for NULL when malloc-ing.
 *  - error reporting.
 *  - finish execute().
 *  - implement loader.
 */

typedef struct Execution {
    unsigned short execution_address = 0;
    bool is_running = true;
} Execution;

unsigned short *read_args(Execution *e, Storage *s, int n_args) {
    unsigned short *args = malloc(n_args * sizeof(*args));
    while (n_args-- > 0) {
        // todo
    }
}

Instruction *lookup(unsigned short instruction_code) {
    // todo
}

int do_step(Execution *e, Storage *s) {
    int *error = malloc(sizeof(*error));
    unsigned short instruction_code = storage_loadmem(s, e->execution_address, error);
    ++e.execution_address;
    if (*error == MEMORY_OP_INVALID_ADDRESS) {
        return false;
    }
    Instruction *instruction = lookup(instruction_code);
    if (instruction == NULL) {
        return false;
    }
    unsigned short *op_args = read_args(e, s, op->n_args);
    op->fn(e, s, op_args);
    free(op_args);
}

void execute(Storage *s) {
    Execution *e = malloc(sizeof(Execution *));
    while (e.is_running) {
        if (!do_step(e, s)) {
            printf("ERROR!\n");
            break;
        }
    }
    free(e);
}
