## Description
An implementation of the [Synacor virtual machine](https://challenge.synacor.com/). Comes with a basic assembler (`assembler.py`), which features syntax sugar such as string printing, comments and memory labels. Here's an extract from an example 50-line FizzBuzz program (viewable in `examples/fizzbuzz.syn`).

```assembly
### Main
set r1 1
loop-start: mod r2 r1 3
eq r2 r2 0
mod r3 r1 5
eq r3 r3 0
and r4 r2 r3
jf r4 not-multiple-of-both
```

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

Or, to use the assembler (requires Python 3):

```
./assembler.py examples/fizzbuzz.syn
./synacor examples/fizzbuzz.bin
```

#### Building / running tests
Requires the Check unit testing library and Valgrind.

```
make test
```
