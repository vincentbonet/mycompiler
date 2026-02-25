cmake_minimum_required(VERSION 3.20)
project(mycompiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mycompiler
  src/main.cpp
  src/lexer.cpp
  src/parser.cpp
  src/ast_printer.cpp
)

target_include_directories(mycompiler PRIVATE include)
target_compile_options(mycompiler PRIVATE -Wall -Wextra -Wpedantic)
