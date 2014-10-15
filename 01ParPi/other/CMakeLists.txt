cmake_minimum_required(VERSION 2.8)

#Project Name
project(PARPI)

# Compiler check
set(COMPILE_FLAGS "-g3 -Os -Wextra -Wall -pedantic -pedantic-errors -std=c++11")

# OpenMP
FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

#Executable macro
macro(executable n)
    if(${ARGC} GREATER 1)
        add_executable(${n} ${ARGN})
        set_target_properties(${n} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})
    else()
        message(SEND_ERROR "Not enough arguments for executable macro.")
    endif()
endmacro()

#Executable
executable(parpi main.cpp)

