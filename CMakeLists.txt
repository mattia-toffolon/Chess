#Author: Alberto Guerrini

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(CMAKE_CXX_FLAGS, "-02")
set(CMAKE_CXX_FLAGS_DEBUG, "-02")
set(CMAKE_CXX_FLAGS_RELEASE, "-02")

# variabile for project name that names the scacchiera executable
set(PROJ_NAME
    scacchiera
)

set(REPLAY_NAME
    replay
)

# set libraries names
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

# iterate over libraries adding them
foreach(LIBRARY ${LIBRARIES}) 
    add_library(${LIBRARY}
        include/${LIBRARY}.hpp
        src/${LIBRARY}.cpp
    )
endforeach(LIBRARY)

# create scacchiera executable
add_executable(${PROJ_NAME}
    src/main.cpp
)
# create replay executable
add_executable(${REPLAY_NAME}
    src/main_replay.cpp
)

# link libraries
target_link_libraries(${PROJ_NAME} ${LIBRARIES})
target_link_libraries(${REPLAY_NAME} ${LIBRARIES})