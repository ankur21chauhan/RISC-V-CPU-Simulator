# RISC-V CPU Simulator

A CPU simulator built from scratch in **C++17**, with the goal of understanding processor architecture, instruction execution, and five-stage pipelining through hands-on implementation.

The project is being developed incrementally, starting with foundational CPU components and progressing toward a pipelined RISC-V processor.

## Project Goals

- Understand how CPU components work together.
- Implement a RISC-V RV32I instruction subset.
- Model registers, instruction execution, and memory operations.
- Build a five-stage instruction pipeline.
- Explore data hazards, forwarding, stalls, and control hazards.
- Measure performance using clock cycles, CPI, and speedup.

## Current Implementation

- [x] C++ project setup
- [x] CMake build configuration
- [x] Register File implementation
- [x] Register initialization and read/write operations
- [x] Enforce the zero-register behavior (`x0`)
- [x] Basic Register File tests

## Planned Features

- [ ] Arithmetic Logic Unit (ALU)
- [ ] RISC-V instruction representation and decoding
- [ ] Instruction execution engine
- [ ] Instruction and data memory models
- [ ] Five-stage pipeline: IF, ID, EX, MEM, WB
- [ ] Pipeline registers between stages
- [ ] Data hazard detection and forwarding
- [ ] Pipeline stalls and branch handling
- [ ] Clock-cycle execution and pipeline visualization
- [ ] CPI, cycle count, and speedup analysis
- [ ] Expanded automated test suite

*Planned features will be marked complete as they are implemented and tested.*

## Architecture

The target processor uses the classic five-stage pipeline:

| Stage | Name | Responsibility |
|---|---|---|
| IF | Instruction Fetch | Fetch the next instruction |
| ID | Instruction Decode | Decode the instruction and read registers |
| EX | Execute | Perform ALU operations and calculate addresses |
| MEM | Memory Access | Read or write data memory |
| WB | Write Back | Write the result to the destination register |

The intended design allows multiple instructions to occupy different stages during the same clock cycle.

## Technology Stack

- **Language:** C++17
- **Build system:** CMake
- **Compiler:** GCC or another compatible C++17 compiler
- **Version control:** Git
- **Testing:** C++ assertions initially; CTest integration planned

## Getting Started

### Prerequisites

Install a C++ compiler, CMake, and Git.

On Ubuntu:

```bash
sudo apt update
sudo apt install build-essential cmake git
```

### Clone the repository

```bash
git clone <YOUR_GITHUB_REPOSITORY_URL>
cd riscv-cpu-simulator
```

Replace the placeholder with your repository's actual clone URL.

### Build the project

```bash
cmake -S . -B build
cmake --build build
```

### Run the current executable

```bash
./build/riscv-sim
```

The executable currently verifies the project foundation. Full RISC-V instruction execution and pipeline simulation are part of the development roadmap.

### Run the Register File tests

Compile the current test directly:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic \
    -Iinclude \
    tests/register_file_test.cpp \
    src/register_file.cpp \
    -o build/register_file_test
```

Run it:

```bash
./build/register_file_test
```

Expected output:

```text
All Register File tests passed!
```

## Project Structure

```text
riscv-cpu-simulator/
├── CMakeLists.txt
├── .gitignore
├── README.md
├── include/
│   └── register_file.hpp
├── src/
│   ├── main.cpp
│   └── register_file.cpp
├── tests/
│   └── register_file_test.cpp
├── examples/
└── docs/
```

The structure will evolve as additional CPU components and tests are introduced.

## Design Principles

- Build each component incrementally.
- Keep interfaces and implementations separate.
- Test component behavior before integrating it.
- Use clear abstractions for CPU state and instruction execution.
- Track development milestones using Git.

## Learning Objectives

This project is intended to build practical understanding of:

- Computer organization and architecture
- RISC-V instruction semantics
- C++ classes, arrays, and modular design
- CPU registers and ALU operations
- Instruction pipelining and hazards
- Debugging, testing, and build systems
- Processor performance metrics

## Project Status

**Early development — foundational components**

The Register File is implemented with basic tests. The five-stage pipeline and instruction execution engine are planned milestones, not yet completed features.

## License

License selection is pending. A license will be added when the project's distribution terms are decided.
