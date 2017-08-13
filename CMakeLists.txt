cmake_minimum_required(VERSION 3.8)
project(Mandelbrot)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
#        Configuration.h Configuration.cpp
#        AVLTree.h Dictionary.h KeyValue.h
        config.h config.cpp
        Utils.h Utils.cpp
        Mandelbrot.cpp Mandelbrot.h)
add_executable(Mandelbrot ${SOURCE_FILES})