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
#include "../include/DrawException.hpp"
#include "time.h"

Match::Match(bool isHuman){
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
    std::cout<<*board<<std::endl;
    bool currentID = Piece::WHITE;
    while(true){
        if(currentID == playerA->get_ID()){
            try{
                playerA->turn();
                std::cout<<*board<<std::endl;
            }
            catch(CheckException e){
                std::cout<<*board<<std::endl;
                std::cout<<e.what()<<std::endl;
                playerB->set_check(true);
                if(playerB->get_safe_moves().size()==0){
                    throw CheckMateException("CheckMate! Player A won!");
                    return true;
                }
            }
        }
        else{
            try{
                playerB->turn();
                std::cout<<*board<<std::endl;
            }
            catch(CheckException e){
                std::cout<<*board<<std::endl;
                std::cout<<e.what()<<std::endl;
                playerA->set_check(true);
                if(playerA->get_safe_moves().size()==0){
                    throw CheckMateException("CheckMate! Player B won!");
                    return true;
                }
            }
        }    

        currentID = !currentID;
    }
    
    return true;
}


#endif  //MATCH_CPP