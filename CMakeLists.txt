cmake_minimum_required(VERSION 3.15)
project(scrabble_junior_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/WORDS.TXT ${CMAKE_CURRENT_BINARY_DIR}/data/WORDS.TXT COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/default.txt ${CMAKE_CURRENT_BINARY_DIR}/data/default.txt COPYONLY)

add_executable(build_board
        BoardBuilder/BoardBuilder.cpp
        BoardBuilder/BoardBuilder.h
        BoardBuilder/build_board.cpp
        data/WORDS.TXT
        Board.cpp
        Board.h
        Word.cpp
        Word.h
        )

add_executable(scrabble_junior
        ScrabbleJunior/scrabble_junior.cpp
        ScrabbleJunior/Player.cpp
        ScrabbleJunior/Player.h
        ScrabbleJunior/Game.cpp
        ScrabbleJunior/Game.h
        Word.cpp
        Word.h
        Board.cpp
        Board.h
        )

