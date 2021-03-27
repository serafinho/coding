cmake_minimum_required(VERSION 3.10)

# set the project name
project(Coding)

SET(CMAKE_BUILD_TYPE Debug)
add_compile_options(-std=c++17 -Wall)

add_subdirectory (cppFeatures)
add_subdirectory (simple)
add_subdirectory (factorial)
add_subdirectory (linkedlists)
add_subdirectory (cpp14)
add_subdirectory (threading)
add_subdirectory (designpatterns)
add_subdirectory (trees)
