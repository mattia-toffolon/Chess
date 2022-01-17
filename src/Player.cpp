//Francesco Stella 2008816
#ifndef PLAYER_CPP
#define PLAYER_CPP
#include<iostream>
#include "../include/Board.hpp"
#include "../include/Player.hpp"

Player::Player(){};
//Costructor with argument ID for the color of the pawns
// and a reference to the chessboard
Player::Player(bool id, Board& b){
    ID = id;
    board = &b;
}

//Return the ID of the player
bool Player::get_ID(){
    return ID;
}

#endif  //PLAYER_CPP