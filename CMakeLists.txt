cmake_minimum_required(VERSION 3.27)
project(PEA_projekt_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(PEA_projekt_1 main.cpp
        Menu.cpp
        Menu.h
        Model.cpp
        Model.h
        algorithms/BruteForce.cpp
        algorithms/BruteForce.h
        Helpers.cpp
        Helpers.h
        App.cpp
        App.h
        algorithms/LittleNew.cpp
        algorithms/LittleNew.h
        algorithms/DynamicProg.cpp
        algorithms/DynamicProg.h
        Config.h
)
