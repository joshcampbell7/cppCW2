cmake_minimum_required(VERSION 3.26)
project(cppCW2)

set(CMAKE_CXX_STANDARD 17)

add_executable(cppCW2 main.cpp
        Object.h
        Object.cpp
        Enemy.h
        Enemy.cpp
        Objective.h
        Objective.cpp
        Room.h
        Room.cpp
        Player.h
        Player.cpp
        jsonParser.h
        jsonParser.cpp
        MainEngine.h
        MainEngine.cpp
        Map.h
        Map.cpp
)
