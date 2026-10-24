# RISC-V CPU Simulator

A RISC-V CPU simulator built from scratch in **C++17** to explore processor architecture, instruction decoding, arithmetic execution, and eventually five-stage instruction pipelining.

The project is being developed incrementally, with an emphasis on modular C++ design, automated testing, and understanding how CPU components work together.

## Project Goals

- Understand how CPU components work together.
- Implement a subset of RISC-V RV32I instructions.
- Model registers, instruction execution, and memory operations.
- Build a five-stage instruction pipeline.
- Explore data hazards, forwarding, stalls, and control hazards.
- Measure performance using clock cycles, CPI, and speedup.

## Current Implementation

- [x] C++17 project setup
- [x] CMake build configuration
- [x] Register File implementation with 32 integer registers
- [x] Register initialization and read/write operations
- [x] Enforce the zero-register behavior (`x0`)
- [x] Register File automated tests
- [x] Arithmetic Logic Unit (ALU) with addition and subtraction
- [x] ALU tests, including unsigned arithmetic edge cases
- [x] R-type instruction field decoding: opcode, `rd`, `funct3`, `rs1`, `rs2`, and `funct7`
- [x] Decoder automated tests
- [x] Basic CPU execution engine
- [x] Register-register `ADD` and `SUB` instruction execution
- [x] Program Counter initialization and advancement by 4 bytes after successful instructions
- [x] CPU tests for arithmetic execution, register behavior, PC updates, and unsupported opcodes
- [x] CTest integration for all four test suites

### Current Limitations

- Only R-type `ADD` and `SUB` instructions are supported by the CPU execution engine.
- Instructions are currently supplied directly to the execution function; instruction-memory fetching and a program execution loop are not implemented yet.
- Immediate instructions, branches, jumps, loads, stores, and a five-stage pipeline are not implemented yet.
- The executable currently demonstrates a single hardcoded `ADD` instruction.

## Planned Features

- [ ] Instruction memory and program execution loop
- [ ] Expanded RV32I instruction support, including immediate and logical operations
- [ ] Data memory and load/store instructions
- [ ] Branch and jump instructions
- [ ] Five-stage pipeline: IF, ID, EX, MEM, WB
- [ ] Pipeline registers between stages
- [ ] Data hazard detection and forwarding
- [ ] Pipeline stalls and branch handling
- [ ] Cycle-by-cycle pipeline trace or visualization
- [ ] CPI, cycle count, and performance analysis
- [ ] Expanded automated test suite and reference validation

*Features will be marked complete only after implementation and testing.*

## Architecture

The current CPU execution engine coordinates three components:

| Component | Responsibility |
|---|---|
| Register File | Stores 32 integer registers and enforces the `x0` zero-register rule |
| ALU | Performs addition and subtraction |
| Decoder | Extracts R-type instruction fields |
| CPU | Decodes supported instructions, reads operands, executes the operation, writes back the result, and advances the PC |

### Planned Five-Stage Pipeline

The target processor will use the classic five-stage pipeline:

| Stage | Name | Responsibility |
|---|---|---|
| IF | Instruction Fetch | Fetch the next instruction |
| ID | Instruction Decode | Decode the instruction and read registers |
| EX | Execute | Perform ALU operations and calculate addresses |
| MEM | Memory Access | Read or write data memory |
| WB | Write Back | Write the result to the destination register |

The intended design will allow multiple instructions to occupy different stages during the same clock cycle.

## Technology Stack

- **Language:** C++17
- **Build system:** CMake
- **Compiler:** GCC or another compatible C++17 compiler
- **Version control:** Git
- **Testing:** C++ assertions integrated with CTest

## Getting Started

### Prerequisites

Install a C++ compiler, CMake, and Git.

On Ubuntu:

```bash
sudo apt update
sudo apt install build-essential cmake git
```

### Clone the Repository

```bash
git clone https://github.com/ankur21chauhan/RISC-V-CPU-Simulator.git
cd RISC-V-CPU-Simulator
```

### Build the Project

```bash
cmake -S . -B build
cmake --build build
```

### Run the Simulator

```bash
./build/riscv-sim
```

The current executable initializes the CPU, sets sample register values, executes a hardcoded `ADD` instruction, and prints the register values before and after execution.

### Run the Automated Tests

```bash
ctest --test-dir build --output-on-failure
```

The test suite currently covers:

- Register File behavior
- ALU operations
- R-type instruction field decoding
- Basic CPU instruction execution

## Project Structure

```text
RISC-V-CPU-Simulator/
├── CMakeLists.txt
├── .gitignore
├── README.md
├── include/
│   ├── register_file.hpp
│   ├── alu.hpp
│   ├── decoder.hpp
│   └── cpu.hpp
├── src/
│   ├── main.cpp
│   ├── register_file.cpp
│   ├── alu.cpp
│   ├── decoder.cpp
│   └── cpu.cpp
├── tests/
│   ├── register_file_test.cpp
│   ├── alu_test.cpp
│   ├── decoder_test.cpp
│   └── cpu_test.cpp
├── examples/
└── docs/
```

The project structure will evolve as additional CPU components and tests are introduced.

## Design Principles

- Build each component incrementally.
- Keep interfaces and implementations separate.
- Test component behavior before integration.
- Use clear abstractions for CPU state and instruction execution.
- Maintain a reproducible build and test workflow.
- Track development milestones using Git.

## Learning Objectives

This project is intended to build practical understanding of:

- Computer organization and architecture
- RISC-V instruction encoding and semantics
- C++ classes and modular design
- Bit manipulation and fixed-width integer arithmetic
- CPU registers, ALU operations, and instruction execution
- Instruction pipelining and hazards
- Debugging, automated testing, and build systems
- Processor performance metrics

## Project Status

**Early development — basic instruction execution implemented.**

The Register File, ALU, Decoder, and a basic CPU execution engine are implemented with automated tests. The current engine supports R-type `ADD` and `SUB` instructions. Instruction-memory fetching, a program execution loop, data memory, and the five-stage pipeline remain planned work.

## License

License selection is pending. A license will be added when the project's distribution terms are decided.
