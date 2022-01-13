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

bool start(){
    return false;
}

#endif  //MATCH_CPP