cmake_minimum_required(VERSION 3.16)
project(fsmImpl)

set(CMAKE_CXX_STANDARD 14)

add_executable(fsmImpl src/main.cpp src/Manager.cpp src/Fsm.cpp)
