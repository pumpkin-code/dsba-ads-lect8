cmake_minimum_required(VERSION 3.0)

project(ADSLecture8_Demos CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 14)

# the following options prevent compiler-optimization issues that are unwanted in an edu process

# with copy-elision optimization (by deafult)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

# with switched copy-elision optimization OFF
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fno-elide-constructors")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -fno-elide-constructors")

#### the list of targets ####
add_executable(ex1_copyelision
        ex1_copyelision/main.cpp
    )

add_executable(ex2_lrvalues
        ex2_lrvalues/main.cpp
    )
    
add_executable(ex3_move
        ex3_move/main.cpp
        ex3_move/safe_array.hpp 
    )
    
add_executable(ex4_delete_def
        ex4_delete_def/main.cpp
    )
