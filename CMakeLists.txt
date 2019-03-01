cmake_minimum_required(VERSION 3.13)
project(load_balancer)

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(Threads)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)

add_executable(main main.cpp ${SOURCES})
target_link_libraries(main PRIVATE ${Boost_LIBRARIES})
target_link_libraries (main PRIVATE ${CMAKE_THREAD_LIBS_INIT})
