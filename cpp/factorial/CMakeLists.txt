cmake_minimum_required(VERSION 3.10)

# set the project name
project(Factorial)

# add the executable
add_executable(Factorial test_factorial.cxx Factorial.h Factorial.cxx)