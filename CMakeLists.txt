# Author: Guerrini Alberto
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# variabile for project name that names the executable
set(PROJ_NAME
    scacchiera
)

set(LIBRARIES
    Board
    King
    Knight
    Pawn
    Piece
    Rook
    Bishop
    Queen
)

project(${PROJ_NAME})

include_directories(/include)

foreach(LIBRARY ${LIBRARIES}) 
    add_library(${LIBRARY}
        include/${LIBRARY}.hpp
        src/${LIBRARY}.cpp
    )
endforeach(LIBRARY)

add_executable(${PROJ_NAME}
    src/main.cpp
)

target_link_libraries(${PROJ_NAME} ${LIBRARIES}) 