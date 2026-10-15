
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
	src/alu.cpp
)

target_include_directories(riscv-sim PRIVATE include)

target_compile_options(riscv-sim PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
)

include(CTest)

if(BUILD_TESTING)

#REGISTER FILE TEST
	add_executable(register_file_test
		tests/register_file_test.cpp
		src/register_file.cpp
	)

	target_include_directories(register_file_test PRIVATE include)
	target_compile_options(register_file_test PRIVATE
		-Wall
		-Wextra
		-Wpedantic
	)

	add_test(
		NAME RegisterFileTest
		COMMAND register_file_test
	)

#ALU TESTS
	add_executable(alu_test
		tests/alu_test.cpp
		src/alu.cpp
	)

	target_include_directories(alu_test PRIVATE include)

	target_compile_options(alu_test PRIVATE
		-Wall
		-Wextra
		-Wpedantic
	)

	add_test(
		NAME ALUTest
		COMMAND alu_test
	)
	


endif()
