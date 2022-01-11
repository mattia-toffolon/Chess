cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(PROJECT_NAME
    Progetto_Dea
)

set(LIBRARIES
    Board
    Piece
    Player
)

project(${PROJECT_NAME})

include_directories(include)

foreach(LIBRARY ${LIBRARIES}) 
    add_library(${LIBRARY}
        include/${LIBRARY}.hpp
        src/${LIBRARY}.cpp
    )
endforeach(LIBRARY)

add_executable(scacchiera
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES}) 