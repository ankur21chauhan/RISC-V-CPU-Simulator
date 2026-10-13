
cmake_minimum_required(VERSION 3.16)

project(RISCV_CPUSimulator
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(riscv-sim
    src/main.cpp
    src/register_file.cpp
)

target_include_directories(riscv-sim PRIVATE include)

target_compile_options(riscv-sim PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
)
