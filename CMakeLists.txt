cmake_minimum_required(VERSION 3.24)
project(heston_model)

set(CMAKE_CXX_STANDARD 17)

add_executable(heston_model main.cpp option_pricer.cpp option_pricer.h)
