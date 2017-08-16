cmake_minimum_required(VERSION 3.8)
project(Mandelbrot)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        MandelConfig.h MandelConfig.cpp
        Utils.h Utils.cpp
        Mandelbrot.cpp Mandelbrot.h LinearColoring.h)
add_executable(Mandelbrot ${SOURCE_FILES})