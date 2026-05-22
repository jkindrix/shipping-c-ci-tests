cmake_minimum_required(VERSION 3.15)
project(portable C)

add_executable(portable main.c portable_setup.c)
target_compile_options(portable PRIVATE
    -Wall -Wextra -Wpedantic)
