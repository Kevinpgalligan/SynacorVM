## Description
My attempt at the [Synacor Challenge](https://challenge.synacor.com/). You are given
a virtual machine specification and a binary-encoded program. Your goal is to develop
the specified virtual machine so that it can execute said program.

The virtual machine is complete. I haven't bothered to complete the rest of the
challenge.

## Setup
#### Building

```
git clone https://github.com/Kevinpgalligan/SynacorInC.git
cd ./SynacorInC
make
```

#### Running

```
./synacor challenge.bin
```

...where challenge.bin is a binary-encoded program in the spec-defined assembly language.

#### Building / running tests
Requires the Check unit testing library and Valgrind.

```
make test
```
