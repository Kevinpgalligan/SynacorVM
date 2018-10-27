#ifndef STORAGE_H
#define STORAGE_H

// 2^15 address space.
#define MEMORY_SIZE 32768
#define REGISTERS 8
// Registers are represented by numbers in the range 32768..32775
#define REGISTER_OFFSET 32768

// Error codes
#define MEMORY_OP_SUCCESS 0
#define MEMORY_OP_INVALID_ADDRESS -1

struct Storage {
    unsigned short memory[MEMORY_SIZE];
    unsigned short registers[REGISTERS];
};
typedef struct Storage Storage;

Storage *storage_init();
void storage_free(Storage *s);
unsigned short storage_loadmem(Storage *s, unsigned short address, int *error);
int storage_setmem(Storage *storage, unsigned short address, unsigned short value);

#endif
