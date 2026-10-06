cmake_minimum_required(VERSION 3.20)
project(OOP_University)

set(CMAKE_CXX_STANDARD 20)

add_executable(OOP_University
        CS213_A1_Part1_S31,S32_20250172_20250510_20251291_20251534.cpp
        Image_Class.h
        stb_image.h
        stb_image_write.h
)
target_include_directories(OOP_University PRIVATE ../OOP_University)

