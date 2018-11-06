#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "storage.h"

int main(int argc, const char *argv[]) {
    FILE *program_file;
    Storage *storage;
    
    if (argc != 2) {
        printf("One (and only one) input argument required: ");
        printf("the path to the binary-encoded program file that is to be executed.\n");
        exit(1);
    }

    program_file = fopen(argv[1], "rb");
    if (program_file == NULL) {
        printf("Could not open program file: %s\n", strerror(errno));
        exit(errno);
    }
    storage = storage_init();
    if (storage == NULL) {
        printf("Could not allocate space for VM memory.");
        exit(1);
    }
    if (storage_load_program(storage, program_file) != MemoryOpSuccess) {
        printf("Failed to load program into memory.\n");
        exit(1);
    }
    fclose(program_file);

    for (unsigned short i = 0u; i < 5u; i++) {
        printf("Value at address %hu: %hu\n", i, storage->memory[i]);
    }
    
    storage_free(storage);

    return 0;
}
