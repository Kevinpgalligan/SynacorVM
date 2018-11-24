#include "storage.h"
#include "execution.h"
#include "instructions.h"
#include <stdbool.h>
#include <stdio.h>

#define LOAD_OR_ERROR(address, num_cells, destination_pointer)\
    if (get_mem(address, num_cells, destination_pointer) != StorageOpSuccess) {\
        set_error(execution, ExecutionMemoryAccessError);\
        return;\
    }\

// Don't need to support instructions with more than 3 args, but
// leave some extra room just in case.
#define MAX_INSTRUCTION_ARGS 10

static unsigned short instruction_buffer[1];
static unsigned short args_buffer[MAX_INSTRUCTION_ARGS];

void set_error(Execution *execution, ExecutionStatus status) {
    execution->status = status;
    execution->is_running = false;
}

static void do_step(Execution *execution) {
    LOAD_OR_ERROR(execution->address, 1u, instruction_buffer);

    Instruction *instruction = lookup_instruction(instruction_buffer[0]);
    if (instruction == NULL) {
        set_error(execution, ExecutionInvalidInstructionError);
        printf("ERROR, unknown instruction code: %hu\n", instruction_buffer[0]);
        return;
    }

    if (instruction->num_args > 0) {
        LOAD_OR_ERROR(execution->address + 1, instruction->num_args, args_buffer);
    }

    // Advance execution address past current instruction and its args.
    // This has to happen BEFORE the instruction is executed, otherwise
    // we invalidate any instructions that change the execution address.
    execution->address += 1 + instruction->num_args;

    instruction->fn(execution, args_buffer);
}

ExecutionStatus execute_program() {
    Execution execution = { 0, true, ExecutionSuccess };
    while (execution.is_running) {
        do_step(&execution);
    }
    return execution.status;
}
