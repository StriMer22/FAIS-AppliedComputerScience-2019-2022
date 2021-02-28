cmake_minimum_required(VERSION 3.17)
project(C__)

set(CMAKE_CXX_STANDARD 11)
#AlgorithmsAndDataStructures/From8To10.cpp
#Numerky/FirstTask.cpp
#Numerky/Test.cpp
#Numerky/householderQR.cpp Numerky/linearalgebra.h
#Numerky/Test2.cpp Numerky/nrutil.h
#AlgorithmsAndDataStructures/Zbiory.cpp
#Numerky/Zadanie1_Thomas.cpp
LINK_DIRECTORIES(gsl)
add_executable(C__ AlgorithmsAndDataStructures/ReversePolishNotation/RPN.cpp)
TARGET_LINK_LIBRARIES(C__ gsl)

