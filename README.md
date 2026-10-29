# RISC-V CPU Simulator

A RISC-V CPU simulator built from scratch in **C++17** to explore processor architecture, instruction decoding, arithmetic execution, control flow, and eventually five-stage instruction pipelining.

The project is being developed incrementally, with an emphasis on modular C++ design, automated testing, and understanding how CPU components work together.

## Project Goals

- Understand how CPU components work together.
- Implement a subset of RISC-V RV32I instructions.
- Model registers, instruction execution, and memory operations.
- Build a five-stage instruction pipeline.
- Explore data hazards, forwarding, stalls, and control hazards.
- Measure performance using clock cycles, CPI, and speedup.

## Current Implementation

### Core Components

- [x] C++17 project setup
- [x] CMake build configuration
- [x] Register File with 32 integer registers
- [x] Register initialization and read/write operations
- [x] Enforce the zero-register behavior (`x0`)
- [x] Arithmetic Logic Unit (ALU) with addition and subtraction
- [x] Instruction Decoder for supported instruction fields and immediates
- [x] Basic CPU instruction execution engine
- [x] Instruction memory using a vector of 32-bit instructions
- [x] Program loading through `loadProgram()`
- [x] Instruction fetching and execution through `step()`
- [x] Program Counter initialization and advancement
- [x] PC alignment checking during instruction fetching
- [x] CMake/CTest integration for four test suites

### Implemented Instructions

| Instruction | Type | Operation | Status |
|---|---|---|---|
| `ADD` | R-type | Add two register values | Implemented |
| `SUB` | R-type | Subtract one register value from another | Implemented |
| `ADDI` | I-type | Add a sign-extended immediate to a register value | Implemented |
| `LUI` | U-type | Load an upper immediate | Implemented |
| `AUIPC` | U-type | Add an upper immediate to the current PC | Implemented |
| `JAL` | J-type | Save the return address and jump to a PC-relative target | Implemented |

These instructions have been integrated into the CPU execution engine. Automated tests cover the core components and supported instruction behavior.

### JAL Testing

The current JAL tests cover:

- Positive jump offsets
- Negative jump offsets
- Saving the return address as `PC + 4`
- Jumping to the calculated target address
- Writing to `x0` without changing its value
- Avoiding an additional normal PC increment after a jump

## Current Limitations

- Only a subset of RV32I instructions is supported.
- `JALR` and conditional branch instructions have not yet been implemented.
- Logical, shift, comparison, and remaining arithmetic instructions are pending.
- Data memory and load/store instructions are not yet implemented.
- The current simulator does not implement a five-stage instruction pipeline.
- Pipeline registers, hazard detection, forwarding, stalls, and branch handling remain future work.
- Performance analysis using CPI, clock cycles, and speedup has not yet been implemented.
- The instruction set and test coverage will expand as development progresses.

## Planned Features

### Phase 1 — Core CPU Components

- [x] Register File
- [x] Arithmetic Logic Unit
- [x] Instruction Decoder
- [x] Basic CPU execution engine
- [x] Automated component tests

### Phase 2 — Expanded Instruction Execution

- [x] `ADD` and `SUB`
- [x] `ADDI`
- [x] `LUI`
- [x] `AUIPC`
- [x] `JAL`
- [ ] `JALR`
- [ ] Conditional branches: `BEQ`, `BNE`, `BLT`, `BGE`, `BLTU`, `BGEU`
- [ ] Remaining selected RV32I arithmetic, logical, comparison, and shift instructions
- [ ] Data memory
- [ ] Load instructions: `LB`, `LH`, `LW`, `LBU`, `LHU`
- [ ] Store instructions: `SB`, `SH`, `SW`
- [ ] Expanded automated tests and edge-case validation

### Phase 3 — Five-Stage Pipeline

- [ ] Instruction Fetch (IF)
- [ ] Instruction Decode (ID)
- [ ] Execute (EX)
- [ ] Memory Access (MEM)
- [ ] Write Back (WB)
- [ ] Pipeline registers between stages
- [ ] Cycle-by-cycle pipeline execution

### Phase 4 — Hazards and Performance

- [ ] Data hazard detection
- [ ] Data forwarding
- [ ] Pipeline stalls
- [ ] Control hazard handling
- [ ] Cycle-by-cycle pipeline trace or visualization
- [ ] Cycle count and CPI calculations
- [ ] Performance analysis and speedup comparisons

**Features will be marked complete only after implementation and testing.**

## Architecture

The current CPU execution engine coordinates the Register File, ALU, Decoder, instruction memory, and Program Counter.

| Component | Responsibility |
|---|---|
| Register File | Stores 32 integer registers and enforces the `x0` zero-register rule |
| ALU | Performs supported arithmetic operations, currently addition and subtraction |
| Decoder | Extracts instruction fields and immediate values |
| CPU | Executes supported instructions, manages register writes, loads programs, fetches instructions, and updates the PC |
| Instruction Memory | Stores the program as 32-bit instruction words |

### Program Execution Flow

The current instruction execution flow is:

1. Load a program into instruction memory using `loadProgram()`.
2. Fetch the instruction at the address specified by the PC.
3. Decode the instruction fields and immediate values.
4. Read the required register operands.
5. Execute the supported operation.
6. Write the result or return address to the destination register, when required.
7. Update the PC according to the instruction's behavior.

The `step()` method fetches and executes one instruction. It returns `false` when execution reaches the end of instruction memory.

### Planned Five-Stage Pipeline

The target processor will use the classic five-stage pipeline:

| Stage | Name | Responsibility |
|---|---|---|
| IF | Instruction Fetch | Fetch the next instruction |
| ID | Instruction Decode | Decode the instruction and read registers |
| EX | Execute | Perform ALU operations and calculate addresses |
| MEM | Memory Access | Read or write data memory |
| WB | Write Back | Write the result to the destination register |

The intended design will allow multiple instructions to occupy different pipeline stages during the same clock cycle.

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

The executable currently demonstrates a small hardcoded program using supported instructions.

### Run the Automated Tests

```bash
ctest --test-dir build --output-on-failure
```

The project currently contains four test suites:

- `RegisterFileTest`
- `ALUTest`
- `DecoderTest`
- `CPUTest`

These test suites cover register behavior, arithmetic operations, instruction decoding, and supported CPU instruction execution.

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

The project structure will evolve as additional CPU components, memory models, and pipeline stages are introduced.

## Design Principles

- Build each component incrementally.
- Keep interfaces and implementations separate.
- Test component behavior before integration.
- Use clear abstractions for CPU state and instruction execution.
- Maintain a reproducible build and test workflow.
- Validate instruction behavior with focused tests and edge cases.
- Track development milestones using Git.

## Learning Objectives

This project is intended to build practical understanding of:

- Computer organization and architecture
- RISC-V instruction encoding and semantics
- C++ classes and modular design
- Bit manipulation and fixed-width integer arithmetic
- CPU registers, ALU operations, and instruction execution
- Instruction fetching and Program Counter management
- Instruction pipelining and hazards
- Debugging, automated testing, and build systems
- Processor performance metrics

## Project Status

**Core CPU components implemented; expanded RV32I instruction support in progress.**

The Register File, ALU, Decoder, instruction memory, and basic CPU execution engine are implemented. The current execution engine supports `ADD`, `SUB`, `ADDI`, `LUI`, `AUIPC`, and `JAL`.

Automated tests cover the four main test suites, including selected positive and negative JAL offsets and return-address behavior.

The next milestones are indirect jumps, conditional branches, additional arithmetic and logical instructions, data memory operations, and eventually the five-stage pipeline with hazard handling and performance analysis.

## License

This project is licensed under the [MIT License](LICENSE).

You are free to use, modify, and distribute this software in accordance with the terms of the license.
