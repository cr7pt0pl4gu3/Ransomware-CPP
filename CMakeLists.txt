cmake_minimum_required(VERSION 3.17)
project(Ransomware_C__)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

configure_file(resources.rc resources.rc)
add_executable(launcher launcher.cpp resources.rc)
add_executable(rsa rsa.cpp)
add_executable(encrypt encrypt.cpp)
add_executable(decrypt decrypt.cpp)