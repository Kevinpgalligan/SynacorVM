## Description
My attempt at the [Synacor Challenge](https://challenge.synacor.com/), which
provides you with a virtual machine specification and a program that the virtual
machine should be able to execute. The program is encoded as a binary blob.

## Setup
Build commands:

```
clang -c -Wall -Wextra -I./include -o build/storage.o src/storage.c
clang -c -Wall -Wextra -I./include -o build/main.o src/main.c
clang -Wall -Wextra -o ./synacor build/*.o
```

To run the virtual machine with the program `challenge.bin`:

```
./synacor challenge.bin
```

To run the tests (requires valgrind):
```
todo
```
