cmake_minimum_required(VERSION 3.20.0)
project(OrderMatchingEngine)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(OrderMatchingEngine main.cpp ${SOURCES})