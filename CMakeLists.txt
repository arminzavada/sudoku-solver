cmake_minimum_required(VERSION 3.25)
project(sudoku)

set(CMAKE_CXX_STANDARD 17)

add_executable(sudoku main.cpp SudokuMove.cpp SudokuMove.h SudokuSolver.cpp SudokuSolver.h Timer.cpp Timer.h)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(sudoku PUBLIC OpenMP::OpenMP_CXX)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")