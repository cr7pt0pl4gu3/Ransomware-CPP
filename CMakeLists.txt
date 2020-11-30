cmake_minimum_required(VERSION 3.17)
project(Ransomware_C__)

set(CMAKE_CXX_STANDARD 11)

add_executable(keygen keygen.cpp)
add_executable(encrypt encrypt.cpp)
add_executable(decrypt decrypt.cpp)