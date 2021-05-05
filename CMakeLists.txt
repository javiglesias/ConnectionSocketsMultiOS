cmake_minimum_required(VERSION 3.13)
project(ConnectionSocketsMultiOS)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Connection.cpp)

add_executable(ConnSample ${SOURCE_FILES})
