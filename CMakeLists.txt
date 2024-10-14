cmake_minimum_required(VERSION 3.27)
project(PEA_projekt_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(PEA_projekt_1 main.cpp
        Menu.cpp
        Menu.h
        MatrixModel.cpp
        MatrixModel.h
        BruteForce.cpp
        BruteForce.h
        Helpers.cpp
        Helpers.h
        App.cpp
        App.h)
