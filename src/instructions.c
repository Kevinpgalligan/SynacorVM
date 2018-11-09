#include "instructions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

InstructionStatusCode halt(Execution *e, Storage *s, unsigned short *args) {
    e->is_running = false;
    return InstructionSuccess;
}

InstructionStatusCode out(Execution *e, Storage *s, unsigned short *args) {
    unsigned short c = *args;
    if (c > SCHAR_MAX) {
        return InstructionArgOutsideAsciiRange;
    }
    printf("%c", (char) c);
    return InstructionSuccess;
}

InstructionStatusCode noop(Execution *e, Storage *s, unsigned short *args) {
    return InstructionSuccess;
}

Instruction instructions[] = {
    { 0,  "halt", &halt, 0 },
    { 19, "out",  &out,  1 },
    { 21, "noop", &noop, 1 }
};

const size_t num_instructions = sizeof instructions / sizeof instructions[0];

Instruction *lookup_instruction(unsigned short code) {
    for (size_t i = 0; i < num_instructions; i++) {
        if (instructions[i].code == code) {
            return &instructions[i];
        }
    }
    return NULL;
}
