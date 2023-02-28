cmake_minimum_required(VERSION 3.17)
project(Assignment1)

set(CMAKE_CXX_STANDARD 14)

add_executable(EDIT
        src/main.cpp src/linked_list.h src/linked_list.cpp src/text_editor.h src/text_editor.cpp)
