//Francesco Stella 2008816
#ifndef MATCH_HPP
#define MATCH_HPP
#include<iostream>
#include "Player.hpp"

//We use this class to start the game if it's
//a computer vs computer or a human vs computer game
class Match
{
private:
    //We use the variable board to access the square 
    //and the pawns of the chessboard
    Board board;
    //Player A is always a computer
    Player playerA;
    //Player B should be a human or a computer
    Player playerB; 
public:
    //Costructor with where the argument is a bool
    //to determine playerB
    Match(bool isHuman);
    //Destructor
    ~Match();
    //Until the value is true, the game is still going on
    //When it became false the game is over
    bool start();
};
#endif  //MATCH_HPP