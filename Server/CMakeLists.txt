cmake_minimum_required(VERSION 3.16)
project(TicTacToeServer)
set(CMAKE_CXX_STANDARD 17)

# Finds sfml package
find_package(SFML 2.5 COMPONENTS system network REQUIRED)

# Sets SOURCES var
set(SOURCES main.cpp)

add_executable(TicTacToeServer ${SOURCES})

target_link_libraries(TicTacToeServer sfml-network sfml-system)