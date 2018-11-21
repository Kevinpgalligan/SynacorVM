#include "storage.h"
#include "execution.h"
#include "instructions.h"
#include <stdbool.h>
#include <stdio.h>

// Initializes a pointer, allocates it memory
// and loads num_cells from storage into
// it. Then advances the execution pointer past
// the cells that were loaded. If any of these
// steps fail, it sets the Execution in an error
// state and returns from the function.
#define LOAD_OR_ERROR(pointer_name, num_cells)\
    pointer_name = malloc(num_cells * sizeof *pointer_name);\
    if (pointer_name == NULL) {\
        set_error(e, ExecutionAllocError);\
        return;\
    }\
    if (storage_get_mem(s, e->address, num_cells, pointer_name) != StorageOpSuccess) {\
        set_error(e, ExecutionMemoryAccessError);\
        return;\
    }\
    e->address += num_cells;

void set_error(Execution *e, ExecutionStatusCode status) {
    e->status = status;
    e->is_running = false;
}

void do_step(Execution *e, Storage *s) {
    unsigned short *instruction_code = NULL;
    LOAD_OR_ERROR(instruction_code, 1)

    Instruction *instruction = lookup_instruction(*instruction_code);
    if (instruction == NULL) {
        set_error(e, ExecutionInvalidInstructionError);
        printf("ERROR, unknown instruction code: %hu\n", *instruction_code);
        return;
    }

    unsigned short *args = NULL;
    if (instruction->num_args > 0) {
        LOAD_OR_ERROR(args, instruction->num_args)
    }

    free(args);
    free(instruction_code);
}

ExecutionStatusCode execute(Storage *s) {
    EXECUTION_INIT(e);
    while (e.is_running) {
        do_step(&e, s);
    }
    return e.status;
}
