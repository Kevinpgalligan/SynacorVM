#!/usr/bin/env python3

"""A hacked-together assembler for the Synacor assembly language.
Includes some necessary syntax sugar such as printing strings, comments
and labels for memory addresses."""

import argparse
import collections
import struct

INSTRUCTIONS = ["halt", "set", "push", "pop", "eq", "gt", "jmp", 
    "jt", "jf", "add", "mult", "mod", "and", "or", "not", "rmem", 
    "wmem", "call", "ret", "out", "in", "noop", "div"]
INSTRUCTION_TO_CODE = {instruction: code for code, instruction in enumerate(INSTRUCTIONS)}

COMMENT_CHARACTER = ";"

LABEL_PLACEHOLDER = 9999

REGISTER_OFFSET = 32768
NUM_REGISTERS = 8

def main():
    parser = argparse.ArgumentParser(description="Synacor language assembler. Performs minimal argument validation.")
    parser.add_argument("f", help="Name of file containing Synacor assembly language.")
    parser.add_argument("out", nargs="?", help="Name of file where binary should be written.")
    args = parser.parse_args()
    
    memory_address = 0
    label_to_memory = {}
    label_placeholders = collections.defaultdict(list)
    lines = open(args.f, "r").readlines()
    with open(args.out if args.out else args.f.replace(".syn", ".bin"), "wb") as out_file:
        for line in lines:
            comment_hash_index = line.find(COMMENT_CHARACTER)
            if comment_hash_index != -1:
                line = line[:comment_hash_index]
            line = line.strip()
            if not line:
                continue
            parts = line.split(" ")
            if parts[0].endswith(":"):
                label_to_memory[parts[0][:-1]] = memory_address
                parts = parts[1:]
            instruction = parts[0]
            if instruction not in INSTRUCTIONS:
                raise Exception("Invalid instruction: " + instruction)
            # Special support for printing strings.
            if instruction == "out" and "\"" in parts[1]:
                s = " ".join(parts[1:]).strip("\"")
                for c in s:
                    out_file.write(to_unsigned_short(INSTRUCTION_TO_CODE[instruction]))
                    memory_address += 1
                    out_file.write(to_unsigned_short(ord(c)))
                    memory_address += 1
                continue
            out_file.write(to_unsigned_short(INSTRUCTION_TO_CODE[instruction]))
            memory_address += 1
            for n, instruction_arg in enumerate(parts[1:]):
                value = None
                try:
                    value = parse_instruction_arg(instruction, n, instruction_arg, label_to_memory)
                except UndefinedLabelException as e:
                    value = LABEL_PLACEHOLDER
                    # Store file position so that we can come back and write
                    # the memory address later.
                    label_placeholders[e.name].append(out_file.tell())
                out_file.write(to_unsigned_short(value))
                memory_address += 1
        # Now go back and write in the missing label values.
        for label, positions in label_placeholders.items():
            if label not in label_to_memory:
                raise Exception("Undefined label: " + label)
            for position in positions:
                out_file.seek(position)
                out_file.write(to_unsigned_short(label_to_memory[label]))

def to_unsigned_short(n):
    return struct.pack("<H", n)

class UndefinedLabelException(Exception):
    def __init__(self, name):
        self.name = name

def parse_instruction_arg(instruction, n, arg, label_to_memory):
    # Special support for labels and registers.
    if instruction in ["jmp", "call"] or (instruction in ["jt", "jf"] and n == 1):
        if arg not in label_to_memory:
            raise UndefinedLabelException(arg)
        return label_to_memory[arg]
    if "r" in arg:
        register_number = int(arg[1])
        if register_number < 1 or register_number > NUM_REGISTERS:
            raise Exception("Invalid register: " + arg)
        return REGISTER_OFFSET + register_number - 1
    value = int(arg)
    if value < 0 or value >= REGISTER_OFFSET:
        raise Exception("Value out of range: " + arg)
    return value

if __name__ == "__main__":
    main()
