cmake_minimum_required(VERSION 4.3)
project(Interpretator)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-D_UCRT)
add_executable(Interpretator main.cpp Methods.cpp)

target_link_options(Interpretator PRIVATE
        -static-libgcc
        -static-libstdc++
)