//Francesco Stella 2008816
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include<iostream>
#include "Board.hpp"

class Player
{
private:
    //Pointer to access the board
    Board* board;
    //Identies the color of the pawn that a player is
    //to use during the game
    bool ID;
public:
    //Costructor
    Player(bool ID, Board& b);
    //pure virtual function to manage each turn
    void turn();
    //Invalidate copy costructor and copy assignement
    //to avoid slicing
    Player(Player&) = delete;
    Player& operator=(Player&) = delete;
};

#endif  //PLAYER_HPP