# System Software and Microprocessors Lab Experiments

Welcome to the repository for experiments conducted in the System Software and Microprocessors Lab. This repository contains implementations of various algorithms and tools related to system software, including assemblers, scheduling algorithms, and assembly language programs.

## Table of Contents

- [2 Pass Assembler](#2-pass-assembler)
  - [Pass 1](#pass-1)
  - [Pass 2](#pass-2)
- [Banker's Algorithm](#bankers-algorithm)
- [CPU Scheduling](#cpu-scheduling)
- [Disk Scheduling](#disk-scheduling)
- [MASM Programs](#masm-programs)

## 2 Pass Assembler

This section includes the implementation of a two-pass assembler.

### Pass 1
- `input.txt`: The source code input file.
- `intermediate.txt`: The intermediate code generated during the first pass.
- `optab.txt`: The opcode table used for symbol resolution.
- `pass1.c`: The C program that performs the first pass of the assembler.
- `symtab.txt`: The symbol table generated during the first pass.

### Pass 2
- `end.txt`: The end record for the object code.
- `header.txt`: The header record for the object code.
- `intermediate.txt`: The intermediate code from Pass 1.
- `objectcode.txt`: The final object code generated.
- `optab.txt`: The opcode table used for symbol resolution.
- `output.txt`: The final output file containing the assembled code.
- `Pass2.c`: The C program that performs the second pass of the assembler.
- `prgmlength.txt`: The length of the program.
- `symtab.txt`: The symbol table generated during the first pass.

## Banker's Algorithm

- `Bankers_algorithm.c`: Implementation of the Banker's Algorithm for deadlock avoidance.

## CPU Scheduling

- `cpuscheduling.c`: Implementation of various CPU scheduling algorithms.
- `images/`: Contains visual representations of the scheduling algorithms.
  - `cpu1.png`
  - `cpu2.png`
  - `cpu3.png`

## Disk Scheduling

- `Disk_scheduling.c`: Implementation of disk scheduling algorithms.
- `a.out`: Compiled output for the disk scheduling program.

## MASM Programs

This section includes assembly language programs written for the MASM assembler.

- `16bit_addition.asm`: Program to perform 16-bit addition.
- `16bit_addition_userinput.asm`: Program for 16-bit addition with user input.
- `sort_asc.asm`: Program to sort numbers in ascending order.

## Getting Started

To run the programs, ensure you have the required compilers installed (e.g., GCC for C programs, MASM for assembly programs). Clone the repository and navigate to the respective directories for each experiment to compile and run the programs.

```bash
git clone https://github.com/yourusername/your-repo.git
cd your-repo
