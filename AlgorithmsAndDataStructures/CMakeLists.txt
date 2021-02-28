cmake_minimum_required(VERSION 3.17)
project(C__)

set(CMAKE_CXX_STANDARD 11)
LINK_DIRECTORIES(gsl)
add_executable(C__ AlgorithmsAndDataStructures/ReversePolishNotation/RPN.cpp)
TARGET_LINK_LIBRARIES(C__ gsl)
