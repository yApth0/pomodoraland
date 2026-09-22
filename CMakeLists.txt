cmake_minimum_required(VERSION 4.4)
project(arena VERSION 0.1 LANGUAGES CXX)
add_compile_options(-fexec-charset=UTF-8)
add_executable(arena main.cpp ./arena/arena.cpp ./arena/duel.cpp ./io/io.cpp)
