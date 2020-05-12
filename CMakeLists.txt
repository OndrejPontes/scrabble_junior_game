cmake_minimum_required(VERSION 3.15)
project(scrabble_junior_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(build_board
        BoardBuilder/BoardBuilder.cpp
        BoardBuilder/BoardBuilder.h
        BoardBuilder/build_board.cpp
        BoardBuilder/data/WORDS.TXT
        Board.cpp Board.h Word.cpp Word.h)

add_executable(scrabble_junior
        ScrabbleJunior/scrabble_junior.cpp
        ScrabbleJunior/Player.cpp
        ScrabbleJunior/Game.cpp
        ScrabbleJunior/Player.h
        ScrabbleJunior/Game.h
        ScrabbleJunior/DATA/TEST_BOARD.TXT
        Word.cpp Word.h
        Board.cpp Board.h)

