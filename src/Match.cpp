//Francesco Stella 2008816
#ifndef MATCH_CPP
#define MATCH_CPP
#include<iostream>
#include "include/Player.hpp"
#include "include/Match.hpp"
#include "include/Computer.hpp"
#include "include/Human.hpp"
#include "include/Board.hpp"
#include "time.h"

//to determine playerB
Match::Match(bool isHuman){
    srand(time(NULL));
    int pawnsColor = rand()%2;
    board = new Board(pawnsColor);
    playerA = Computer::Computer((bool)pawnsColor, board);
    if(isHuman){
    playerB = Human::Human(!((bool)pawnsColor), board);
    }
    else{
        playerB = Computer::Computer(!((bool)pawnsColor, board));
    }
}
    

//Until the value is true, the game is still going on
//When it became false the game is over
bool start(){
    return false;
}

#endif  //MATCH_CPP