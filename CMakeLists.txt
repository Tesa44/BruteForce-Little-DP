cmake_minimum_required(VERSION 3.27)
project(PEA_projekt_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

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
        algorithms/Little.cpp
        algorithms/Little.h
        algorithms/DynamicProg.cpp
        algorithms/DynamicProg.h
        Config.h
)
