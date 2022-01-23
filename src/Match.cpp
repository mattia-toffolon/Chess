//Francesco Stella 2008816
#ifndef MATCH_CPP
#define MATCH_CPP
#include<iostream>
#include <time.h>
#include <climits>
#include "../include/Player.hpp"
#include "../include/Match.hpp"
#include "../include/Computer.hpp"
#include "../include/Human.hpp"
#include "../include/Board.hpp"
#include "../include/CheckMateException.hpp"
#include "../include/DrawException.hpp"

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
        max_turns = INT_MAX;
    }
    else{
        playerB =  new Computer((bool)piecesColor, *board);
        max_turns = 30;
    }   
}

Match::~Match(){
    delete board;
    board = nullptr;
    delete playerA;
    playerA = nullptr;
    delete playerB;
    playerB = nullptr;
}

bool Match::start(){
    std::cout<<*board<<std::endl;
    bool currentID = Piece::WHITE;
    int turn_counter=0;
    while(true){
        if(turn_counter>=max_turns)
            throw DrawException("Draw: maximum number of turns reached for this type of Match");

        // checks the times this board occured, if >=3 the it's a Draw
        if(board->get_moves_counter() == 0)
            board_register.erase(board_register.begin(), board_register.end());
        else{
            std::string this_board = board->to_string();
            if(std::find(board_register.begin(), board_register.end(), std::make_pair(this_board, 1)) != board_register.end())
                std::replace(board_register.begin(), board_register.end(), std::make_pair(this_board, 1), std::make_pair(this_board, 2));
            else if(std::find(board_register.begin(), board_register.end(), std::make_pair(this_board, 2)) != board_register.end())
                throw DrawException("Draw: The same board occoured 3 times during this Match");
            else    
                board_register.push_back(std::make_pair(this_board, 1));
        }

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

        turn_counter++;
        currentID = !currentID;
    }
    
    return true;
}


#endif  //MATCH_CPP