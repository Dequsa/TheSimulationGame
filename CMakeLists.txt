cmake_minimum_required(VERSION 4.0)
project(C__1)

set(CMAKE_CXX_STANDARD 20)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

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
        Animals/Human.cpp
        Animals/Human.h
        Plants/Hogweed.cpp
        Plants/Hogweed.h
        Animals/Human.cpp
        Animals/Human.h
main
        Plants/Belladona.cpp
        Plants/Grass.cpp
        Plants/Guarana.cpp
        Plants/SowThistle.cpp
)

target_link_libraries(C__1 ${CURSES_LIBRARIES})
