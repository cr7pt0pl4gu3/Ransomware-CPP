cmake_minimum_required(VERSION 3.17)
project(Ransomware_C__)

set(CMAKE_CXX_STANDARD 11)

add_executable(Ransomware_C__ main.cpp keygen.cpp aes256.hpp aes256.cpp encrypt.cpp decrypt.cpp)