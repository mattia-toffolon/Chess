cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(Progetto Dea)

include_directories(include)

add_library(Board
    include/Board.hpp
    src/Board.hpp
)
add_library(Piece
    include/Piece.hpp
    src/Piece.hpp
)
add_library(Player
    include/Player.hpp
    src/Player.hpp
)