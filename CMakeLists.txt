cmake_minimum_required(VERSION 4.0)
project(C__1)

set(CMAKE_CXX_STANDARD 20)

add_executable(C__1 main.cpp
        main.h
        WorldManager.cpp
        WorldManager.h
        Organism.cpp
        Organism.h
        Animals.cpp
        Animals.h
        Plants.cpp
        Plants.h
        Matrix.cpp
        Matrix.h
        Animals/Wolf.cpp
        Animals/Wolf.h
        Animals/Sheep.cpp
        Animals/Sheep.h
        Animals/Fox.cpp
        Animals/Fox.h
        Animals/Turtle.cpp
        Animals/Turtle.h
        Animals/Antelope.cpp
        Animals/Antelope.h
        Utils.h
        Utils.cpp
)
