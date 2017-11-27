project(FileTyping)

cmake_minimum_required(VERSION 2.6)

include(CTest)
enable_testing()

find_library(magic REQUIRED)

# Flags
set(CMAKE_BUILD_TYPE "RELEASE")

## C++14 flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
## Optimizations
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")

# Executable
add_executable(file_typing main.cpp Magic.cpp)
target_link_libraries(file_typing magic)

# Tests
add_test(NAME test_image COMMAND ./file_typing ../data/test.jpg)
add_test(NAME test_text COMMAND ./file_typing ../data/test.txt)

add_test(NAME test_cmp_image COMMAND ./file_typing ../data/test.jpg "image/jpeg")
add_test(NAME test_cmp_text COMMAND ./file_typing ../data/test.txt "text/plain")
