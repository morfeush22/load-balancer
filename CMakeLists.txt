cmake_minimum_required(VERSION 3.13)
project(load_balancer)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        src/*.h
        src/*.c
        )

add_executable(main main.cpp ${SOURCES})
