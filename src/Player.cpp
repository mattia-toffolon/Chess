//Francesco Stella 2008816
#ifndef PLAYER_CPP
#define PLAYER_CPP
#include<iostream>
#include "src/Board.cpp"
#include "include/Player.hpp"

//Costructor with argument ID for the color of the pawns
// and a reference to the chessboard
Player::Player(bool id, Board& b){
    ID = id;
    board = &b;
}

#endif  //PLAYER_CPP