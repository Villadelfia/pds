cmake_minimum_required(VERSION 2.8)

#Project Name
project(CONV)

# Compiler check
set(COMPILE_FLAGS "-g3 -Os -Wextra -Wall -pedantic -pedantic-errors -std=c++11")

# Qt
set(CMAKE_AUTOMOC ON)
if(APPLE)
    FIND_PACKAGE(Qt5Gui REQUIRED)
    FIND_PACKAGE(Qt5Core REQUIRED)
else()
    FIND_PACKAGE(Qt4 REQUIRED)
    if(QT4_FOUND)
        INCLUDE(${QT_USE_FILE})
        ADD_DEFINITIONS(${QT_DEFINITIONS})
    endif()
endif()

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
        if(APPLE)
            TARGET_LINK_LIBRARIES(${n} Qt5::Gui Qt5::Core)
        else()
            TARGET_LINK_LIBRARIES(${n} ${QT_LIBRARIES})
        endif()
    else()
        message(SEND_ERROR "Not enough arguments for executable macro.")
    endif()
endmacro()

#Executable
executable(conv main.cpp)
