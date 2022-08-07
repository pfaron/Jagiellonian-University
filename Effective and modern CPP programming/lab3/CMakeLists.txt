cmake_minimum_required(VERSION 3.21)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(func_exec function_pointers.cpp)
add_executable(lamb_expr lambda_expressions.cpp)
add_executable(printer printer.cpp)
