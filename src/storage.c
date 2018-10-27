#include "storage.h"
#include <stdbool.h>
#include <stdlib.h>

Storage *storage_init() {
    // Initialize storage with everything set to 0.
    return calloc(1, sizeof(Storage));
} 

void storage_free(Storage *s) {
    free(s);
}

bool valid_address(unsigned short address) {
    return address < MEMORY_SIZE;
}

unsigned short storage_loadmem(Storage *s, unsigned short address, int *error) {
    if (!valid_address(address)) {
        *error = MEMORY_OP_INVALID_ADDRESS;
        return 0;
    }
    *error = MEMORY_OP_SUCCESS;
    return s->memory[address];
}

int storage_setmem(Storage *s, unsigned short address, unsigned short value) {
    if (!valid_address(address)) {
        return MEMORY_OP_INVALID_ADDRESS;
    }
    s->memory[address] = value;
    return MEMORY_OP_SUCCESS;
}
