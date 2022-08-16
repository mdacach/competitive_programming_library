cmake_minimum_required(VERSION 3.21)
project(main)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -Wall -Wextra -Wshadow -Wnon-virtual-dtor \
    -pedantic -Wold-style-cast -Wcast-align \
    -Woverloaded-virtual -Wpedantic -Wconversion \
    -Wsign-conversion -Wmisleading-indentation \
    -Wduplicated-cond -Wduplicated-branches \
    -Wlogical-op -Wnull-dereference \
    -Wuseless-cast -Wdouble-promotion \
    -Wformat=2 -fsanitize=address \
    -fsanitize=undefined")


add_executable(main main.cpp)
