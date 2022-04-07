cmake_minimum_required(VERSION 3.21)
project(TicTacToeClient)
set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    # Add sfml package path
    set(SFML_DIR D:/Program\ Files/SFML/build/)
endif()


# Finds sfml package
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Sets SOURCES var
#set(SOURCES main.cpp game.cpp game.h multiplayer.cpp multiplayer.h windowFunc.cpp windowFunc.h player.hpp)
set(SOURCES main.cpp game/game.cpp game/game.h gui/gui.cpp gui/gui.h game/network.cpp game/network.h gui/button.cpp gui/button.h)

add_executable(TicTacToeClient ${SOURCES})

target_link_libraries(TicTacToeClient sfml-graphics sfml-network sfml-window sfml-system)

set_target_properties(TicTacToeClient PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})