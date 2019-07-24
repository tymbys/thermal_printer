cmake_minimum_required(VERSION 3.13)
project(ThermalPrinter)

set(CMAKE_CXX_STANDARD 14)

add_executable(ThermalPrinter
        main.cpp
        Thermal.cpp
        fb.cpp
        fb.h
        )