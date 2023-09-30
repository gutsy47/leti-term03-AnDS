cmake_minimum_required(VERSION 3.26)
project(practice01)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        practice01 main01.cpp
        application.cpp
        application.h
        structures/dl_list.h
        structures/dl_list.cpp
        structures/dynamic_array.h
        structures/dynamic_array.cpp
        structures/stack.h
        structures/stack.cpp
)
