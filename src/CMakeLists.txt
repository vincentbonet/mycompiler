cmake_minimum_required(VERSION 3.20)
project(mycompiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(mycompiler
  src/main.cpp
  src/lexer.cpp
)

target_include_directories(mycompiler PRIVATE include)

if (MSVC)
  target_compile_options(mycompiler PRIVATE /W4)
else()
  target_compile_options(mycompiler PRIVATE -Wall -Wextra -Wpedantic)
endif()
