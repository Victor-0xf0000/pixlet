cmake_minimum_required(VERSION 3.10)

project(pixlet)

add_executable(pixlet src/main.c)

target_include_directories(pixlet PUBLIC include/)
