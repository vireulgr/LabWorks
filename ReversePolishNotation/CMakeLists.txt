cmake_minimum_required(VERSION 3.3)

project(ReversePolishNotation)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(${PROJECT_NAME} main.cpp Parser.cpp Lexem.cpp RPNComputer.cpp)

