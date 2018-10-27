#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "storage.h"

int main(int argc, const char *argv[]) {
    Storage *s = storage_init();
    int *error = malloc(sizeof(int*));

    unsigned short x = storage_loadmem(s, 0, error);
    assert(*error == MEMORY_OP_SUCCESS);
    assert(x == 0);

    storage_setmem(s, 0, 3);
    assert(*error == MEMORY_OP_SUCCESS);

    x = storage_loadmem(s, 0, error);
    printf("Here's the value of x: %hu\n", x);
    assert(*error == MEMORY_OP_SUCCESS);
    assert(x == 3);

    free(error);
    storage_free(s);
}
