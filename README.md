## Description
My attempt at the [Synacor Challenge](https://challenge.synacor.com/), which
provides you with a virtual machine specification and a program that the virtual
machine should be able to execute. The program is encoded as a binary blob.

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
