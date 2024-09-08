cmake_minimum_required(VERSION 3.1)
project("snake_project")

#set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "/home/projects/snake/SFML")

find_package(SFML 2 COMPONENTS audio graphics window system REQUIRED)

set(SOURCES
    main.cpp
    Game.cpp 
    Board.cpp
)

add_executable(snake ${SOURCES})
target_link_libraries(snake sfml-graphics sfml-audio)