cmake_minimum_required(VERSION 3.3)
project(eternity)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES
    affichage.c
    affichage.h
    color.c
    color.h
    eternity.c
    eternity.h
    functions.c
    functions.h)

add_executable(eternity ${SOURCE_FILES})

target_link_libraries(eternity SDL SDL_gfx)