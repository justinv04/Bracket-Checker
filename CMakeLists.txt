cmake_minimum_required(VERSION 3.15)
project(Assignment3_brackets)

set(CMAKE_CXX_STANDARD 17)

file(COPY test_data/ DESTINATION test_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

# Create the executable for checking
add_executable(check_brackets_Array check_brackets_Array.cpp DSStack.cpp DSList.cpp) # created two executables for array and list
add_executable(check_brackets_List check_brackets_List.cpp DSStack.cpp DSList.cpp)

set(CMAKE_VERBOSE_MAKEFILE OFF)

# testing with the single_include versions of Catch2 V2 (in directory catch2)
include(CTest)
add_executable(tests_list test_DSList.cpp DSList.cpp)
add_test(NAME TestList COMMAND tests_list)
add_executable(tests_stack test_DSStack.cpp DSStack.cpp)
add_test(NAME TestStack COMMAND tests_stack)
