#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "storage.h"
#include "execution.h"
#include "stack.h"

int main(int argc, const char *argv[]) {
    Stack *stack;
    FILE *program_file;
    
    if (argc != 2) {
        printf("One (and only one) input argument required: ");
        printf("the path to the binary-encoded program file that is to be executed.\n");
        exit(1);
    }

    stack = stack_init();
    if (stack == NULL) {
        printf("Could not allocate memory for VM stack.");
        exit(1);
    }
    set_stack(stack);
    
    program_file = fopen(argv[1], "rb");
    if (program_file == NULL) {
        printf("Could not open program file: %s\n", strerror(errno));
        exit(errno);
    }
    if (load_program(program_file) != StorageOpSuccess) {
        printf("Failed to load program into memory.\n");
        exit(1);
    }
    fclose(program_file);

    ExecutionStatus status = execute_program();
    printf("\n-------\n");
    if (status == ExecutionSuccess) {
        printf("Execution was successful!\n");
    } else {
        printf("Execution was unsuccessful! Error code: %d\n", status);
    }
    
    stack_free(stack);

    return 0;
}
