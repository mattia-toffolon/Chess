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

Match::Match(const bool isHuman){
    srand(time(NULL));
    //Random colors for the players
    int piecesColor = std::rand()%2;
    board = new Board((bool)piecesColor);
    //PlayerA is always a computer
    playerA =  new Computer(!(bool)piecesColor, *board);
    //First case: playerB is a Human. Second case: playerB is another computer
    if(isHuman){
        playerB =  new Human((bool)piecesColor, *board);
    }
    else{
        playerB =  new Computer((bool)piecesColor, *board);
    }   
}

bool Match::start(){
    bool currentID=Piece::WHITE;

    while(true){
        if(playerA->get_ID() == currentID){
            playerA->turn();
        }
        else{
            playerB->turn();
        }

        currentID = !currentID;
    }




    /*
    try
    {
        if(playerA->get_ID() == Piece::WHITE){
        playerA->turn();
        playerB->turn();
        }
        else{
        playerB->turn();
        playerA->turn();
        }
    }
    catch(CheckMateException e)
    {
        std::cout << "Checkmate!!! The game is done"<<std::endl;
        return false;
    }
    */
    
    return true;
}


#endif  //MATCH_CPP