# RISC-V CPU Simulator

A RISC-V CPU simulator built from scratch in **C++17** to explore processor architecture, instruction decoding, arithmetic execution, control flow, memory operations, and eventually five-stage instruction pipelining.

The project is developed incrementally, emphasizing modular C++ design, automated testing, architectural correctness, and understanding how CPU components work together.

## Project Goals

- Understand how CPU components work together.
- Implement a selected subset of RISC-V RV32I instructions.
- Model registers, instruction execution, and data memory operations.
- Build a five-stage instruction pipeline.
- Explore data hazards, forwarding, stalls, and control hazards.
- Measure performance using clock cycles, CPI, and speedup.

---

## Current Implementation

### Core Components

- [x] C++17 project setup
- [x] CMake build configuration
- [x] Register file with 32 integer registers
- [x] Register initialization and read/write operations
- [x] Enforce zero-register behavior (`x0`)
- [x] Arithmetic Logic Unit (ALU)
- [x] Instruction decoder for supported instruction fields and immediates
- [x] Basic CPU instruction execution engine
- [x] Instruction memory using a vector of 32-bit instructions
- [x] Program loading through `loadProgram()`
- [x] Instruction fetching and execution through `step()`
- [x] Program Counter initialization and advancement
- [x] PC alignment checking during instruction fetching
- [x] Byte-addressable data memory
- [x] Little-endian memory read and write operations
- [x] Data memory bounds checking
- [x] CMake/CTest integration for four test suites

### Implemented Instructions

The CPU currently supports the following selected RV32I instructions.

| Instruction | Type | Operation | Status |
|---|---|---|---|
| `ADD` | R-type | Add two registers | Implemented |
| `SUB` | R-type | Subtract two registers | Implemented |
| `SLT` | R-type | Signed comparison | Implemented |
| `SLTU` | R-type | Unsigned comparison | Implemented |
| `AND` | R-type | Bitwise AND | Implemented |
| `OR` | R-type | Bitwise OR | Implemented |
| `XOR` | R-type | Bitwise XOR | Implemented |
| `SLL` | R-type | Logical left shift | Implemented |
| `SRL` | R-type | Logical right shift | Implemented |
| `SRA` | R-type | Arithmetic right shift | Implemented |
| `ADDI` | I-type | Add immediate | Implemented |
| `ANDI` | I-type | Bitwise AND immediate | Implemented |
| `ORI` | I-type | Bitwise OR immediate | Implemented |
| `XORI` | I-type | Bitwise XOR immediate | Implemented |
| `SLLI` | I-type | Logical left shift immediate | Implemented |
| `SRLI` | I-type | Logical right shift immediate | Implemented |
| `SRAI` | I-type | Arithmetic right shift immediate | Implemented |
| `LB` | I-type | Load byte (signed) | Implemented |
| `LH` | I-type | Load halfword (signed) | Implemented |
| `LW` | I-type | Load word | Implemented |
| `LBU` | I-type | Load byte (unsigned) | Implemented |
| `LHU` | I-type | Load halfword (unsigned) | Implemented |
| `LUI` | U-type | Load upper immediate | Implemented |
| `AUIPC` | U-type | Add upper immediate to PC | Implemented |
| `JAL` | J-type | Jump and link | Implemented |
| `JALR` | I-type | Jump and link register | Implemented |
| `BEQ` | B-type | Branch if equal | Implemented |
| `BNE` | B-type | Branch if not equal | Implemented |
| `BLT` | B-type | Branch if signed less than | Implemented |
| `BGE` | B-type | Branch if signed greater than or equal | Implemented |
| `BLTU` | B-type | Branch if unsigned less than | Implemented |
| `BGEU` | B-type | Branch if unsigned greater than or equal | Implemented |
| `SB` | S-type | Store byte | Implemented |
| `SH` | S-type | Store halfword | Implemented |
| `SW` | S-type | Store word | Implemented |

**Instruction support is limited to the selected RV32I subset listed above. This project does not claim complete RV32I compliance.**

### Instruction Testing

Automated tests cover selected instruction behavior, including:

- Arithmetic and logical operations.
- Signed and unsigned comparisons.
- Immediate extraction and sign extension.
- Shift operations and malformed shift encodings.
- Positive and negative jump offsets.
- Return address calculation (`PC + 4`).
- Conditional branch taken and not-taken behavior.
- Signed and unsigned branch comparisons.
- Load and store integration.
- Signed and unsigned byte/halfword loading.
- Data memory byte ordering and bounds checking.
- Register zero behavior.
- Unsupported instruction rejection.

CPU integration tests verify that stores and loads operate correctly through the CPU execution engine.

Test coverage will continue to expand as the simulator develops.

---

## Project Architecture

The CPU execution engine coordinates the following components:

| Component | Responsibility |
|---|---|
| Register File | Stores 32 integer registers and enforces the `x0` zero-register rule |
| ALU | Performs supported arithmetic, logical, comparison, and shift operations |
| Decoder | Extracts instruction fields and immediate values |
| CPU | Executes supported instructions and manages processor state |
| Instruction Memory | Stores program instructions as 32-bit words |
| Data Memory | Provides byte-addressable memory for load and store instructions |

### Data Memory

The simulator includes a byte-addressable data memory implemented using a C++ vector of 8-bit values.

Features include:

- Byte, halfword, and word read operations.
- Byte, halfword, and word write operations.
- Little-endian memory representation.
- Address bounds checking.
- Integration with CPU load and store instructions.

The CPU currently initializes its data memory with a size of 1024 bytes.

### Program Execution Flow

1. Load a program into instruction memory using `loadProgram()`.
2. Fetch the instruction at the address specified by the PC.
3. Decode the instruction fields and immediate values.
4. Read the required register operands.
5. Execute the supported operation.
6. Access data memory when required.
7. Write the result to the destination register when required.
8. Update the PC according to the instruction's behavior.

The `step()` method fetches and executes one instruction. It returns `false` when execution reaches the end of instruction memory.

---

## Development Roadmap

### Phase 1 — Core CPU Components

- [x] Register File
- [x] Arithmetic Logic Unit
- [x] Instruction Decoder
- [x] Basic CPU execution engine
- [x] Automated component tests

**Status: Completed**

### Phase 2 — Expanded Instruction Execution

- [x] `ADD` and `SUB`
- [x] `ADDI`
- [x] `LUI`
- [x] `AUIPC`
- [x] `JAL`
- [x] `JALR`
- [x] Conditional branches: `BEQ`, `BNE`, `BLT`, `BGE`, `BLTU`, `BGEU`
- [x] Selected arithmetic, logical, comparison, and shift instructions
- [x] Data memory implementation
- [x] Load instructions: `LB`, `LH`, `LW`, `LBU`, `LHU`
- [x] Store instructions: `SB`, `SH`, `SW`
- [x] Expanded automated tests and CPU integration tests

**Status: Implementation completed; four CTest suites passing.**

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
- [ ] Control-hazard handling
- [ ] Cycle-by-cycle pipeline trace or visualization
- [ ] Cycle count and CPI calculations
- [ ] Performance analysis and speedup comparisons

**Features will be marked complete only after implementation and testing.**

---

## Planned Five-Stage Pipeline

The next major architectural milestone is implementing the classic five-stage processor pipeline.

| Stage | Name | Responsibility |
|---|---|---|
| IF | Instruction Fetch | Fetch the next instruction |
| ID | Instruction Decode | Decode the instruction and read registers |
| EX | Execute | Perform ALU operations and calculate addresses |
| MEM | Memory Access | Read or write data memory |
| WB | Write Back | Write the result to the destination register |

The intended design will allow multiple instructions to occupy different pipeline stages during the same clock cycle.

---

## Technology Stack

- **Language:** C++17
- **Build system:** CMake
- **Compiler:** GCC or another compatible C++17 compiler
- **Version control:** Git
- **Testing:** C++ assertions integrated with CTest

---

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

### Run Automated Tests

```bash
ctest --test-dir build --output-on-failure
```

The project currently contains four test suites:

- `RegisterFileTest`
- `ALUTest`
- `DecoderTest`
- `CPUTest`

The current local test run reports all four suites passing.

---

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
│   ├── cpu.hpp
│   └── data_memory.hpp
├── src/
│   ├── main.cpp
│   ├── register_file.cpp
│   ├── alu.cpp
│   ├── decoder.cpp
│   ├── cpu.cpp
│   └── data_memory.cpp
├── tests/
│   ├── register_file_test.cpp
│   ├── alu_test.cpp
│   ├── decoder_test.cpp
│   └── cpu_test.cpp
├── examples/
└── docs/
```

The project structure will evolve as additional CPU components, memory models, and pipeline stages are introduced.

---

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

- Computer organization and architecture.
- RISC-V instruction encoding and semantics.
- C++ classes and modular design.
- Bit manipulation and fixed-width integer arithmetic.
- CPU registers, ALU operations, and instruction execution.
- Instruction fetching and Program Counter management.
- Data memory and load/store operations.
- Instruction pipelining and hazards.
- Debugging, automated testing, and build systems.
- Processor performance metrics.

---

## Project Status

**Phase 1 and Phase 2 implementation completed.**

The simulator currently includes a Register File, ALU, Instruction Decoder, instruction memory, CPU execution engine, and byte-addressable data memory.

It supports a selected subset of RV32I instructions covering arithmetic, logical operations, comparisons, shifts, immediate operations, jumps, branches, loads, and stores.

The project currently has four CTest suites, with the latest local test run reporting all four passing.

The next development milestone is **Phase 3: Five-Stage Instruction Pipeline**, followed by hazard handling and performance analysis.

---

## License

This project is licensed under the [MIT License](LICENSE).

You are free to use, modify, and distribute this software in accordance with the terms of the license.
