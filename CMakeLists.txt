# Author: Guerrini Alberto
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS, "-02")
set(CMAKE_CXX_FLAGS_DEBUG, "-02")
set(CMAKE_CXX_FLAGS_RELEASE, "-02")

# variabile for project name that names the executable
set(PROJ_NAME
    scacchiera
)

set(LIBRARIES
    Match
    Board
    King
    Knight
    Pawn
    Piece
    Rook
    Bishop
    Queen
    Logger
    Player
    Computer
    Human
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
add_executable(replay
    src/main_replay.cpp
)

target_link_libraries(${PROJ_NAME} ${LIBRARIES})
target_link_libraries(replay ${LIBRARIES}) 