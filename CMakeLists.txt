cmake_minimum_required(VERSION 3.15)
project(scrabble_junior_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(build_board
        BoardBuilder/BoardBuilder.cpp
        BoardBuilder/BoardBuilder.h
        BoardBuilder/build_board.cpp
        BoardBuilder/data/WORDS.TXT
        )
        
add_executable(scrabble_junior
        ScrabbleJunior/scrabble_junior.cpp
        ScrabbleJunior/ScrabbleJunior.cpp
        ScrabbleJunior/ScrabbleJunior.h
        )