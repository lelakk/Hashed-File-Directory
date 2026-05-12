add_executable(new_target main.cpp)
cmake_minimum_required(VERSION 3.10)

project(KatalogProjekt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(KatalogProjekt main.cpp katalog.cpp
        KatalogChain.cpp
        KatalogChain.hpp)