//Francesco Stella 2008816
#ifndef MATCH_CPP
#define MATCH_CPP
#include<iostream>
#include "../include/Player.hpp"
#include "../include/Match.hpp"
#include "../include/Computer.hpp"
#include "../include/Human.hpp"
#include "../include/Board.hpp"
#include "../include/CheckMateException.hpp"
#include "time.h"

Match::Match(bool isHuman){
    srand(time(NULL));
    //Random colors for the players
    int pawnsColor = std::rand()%2;
    board = new Board(pawnsColor);
    //PlayerA is always a computer
    playerA = &Computer((bool)pawnsColor, *board);
    //First case: playerB is a Human. Second case: playerB is another computer
    if(isHuman){
        playerB = &Human(!((bool)pawnsColor), *board);
    }
    else{
        playerB = &Computer(!((bool)pawnsColor), *board);
    }   
}

bool Match::start(){

    try
    {
        if((*playerA).get_ID() == Piece::WHITE){
        (*playerA).turn();
        (*playerB).turn();
    }
    else{
        (*playerB).turn();
        (*playerA).turn();
    }
    }
    catch(CheckMateException e)
    {
        std::cout << "Checkmate!!! The game is done"<<std::endl;
        return false;
    }
    
    return true;
}


#endif  //MATCH_CPP