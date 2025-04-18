cmake_minimum_required(VERSION 3.24)
project(Projet_Vector__Text_based_Editor C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet_Vector__Text_based_Editor main.c shapes/shapes.h shapes/shapes.c area/area.h area/area.c Command/command.h Command/command.c id/id.h id/id.c)
