cmake_minimum_required(VERSION 3.10)

project(pixlet)

add_executable(pixlet src/main.c)

target_include_directories(pixlet PUBLIC include/)
target_link_libraries(pixlet PUBLIC mingw32 SDL2main SDL2 SDL2_image)
