cmake_minimum_required(VERSION 3.26)
project(cppCW2)

set(CMAKE_CXX_STANDARD 17)

add_executable(cppCW2 main.cpp
        Objective.h
        Room.h
        Player.h
        Objective.cpp
        Room.cpp)
