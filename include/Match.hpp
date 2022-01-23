//Francesco Stella 2008816
#ifndef MATCH_HPP
#define MATCH_HPP
#include<iostream>
#include "Player.hpp"
#include "Board.hpp"

//We use this class to start the game if it's
//a computer vs computer or a human vs computer game
class Match
{
protected:
    //We use the variable board to access the square 
    //and the pawns of the chessboard
    Board* board;
    //Player A is always a computer
    Player* playerA;
    //Player B can be a human or a computer
    Player* playerB; 
    // vector that contains the various Boards that occoured during the Match accompained by the times that each one occoured
    // it gets erased whenever a Pawn moves or a Piece gets captured since they're non-return points in the Match
    std::vector<std::pair<std::string, int>> board_register;
    //determines the maxium number of turns for this match
    int max_turns;
public:
    //Costructor with where the argument is a bool
    //to determine playerB
    Match(bool isHuman);
    ~Match();
    //Until the value is true, the game is still going on
    //When it became false the game is over
    bool start();
};

//#include "../src/Match.cpp"

#endif  //MATCH_HPP