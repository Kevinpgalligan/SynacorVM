## Description
My attempt at the [Synacor Challenge](https://challenge.synacor.com/), which
provides you with the specification for a virtual machine and a program that
the virtual machine should be able to execute. The program is encoded as a
binary blob.

## Setup
(Doesn't work yet).

Go to the base directory.

To build:
```
make
```

To execute the code in a binary-encoded file called BLAH:
```
./synacor BLAH
```

To run the tests (requires valgrind):
```
make test
```
