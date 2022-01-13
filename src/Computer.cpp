//Francesco Stella 2008816
#ifndef COMPUTER_CPP
#define COMPUTER_CPP
#include "../include/Player.hpp"
#include "../include/Computer.hpp"
#include "../include/Piece.hpp"
#include<iostream>
#include<vector>
#include "time.h"

//Function that control the turn
void turn(){
    std::cout<<"Mossa del computer:"<<std::endl;
    std::string from = "";
    std::string to = "";
    srand(time(NULL));

    try{
        Piece* random_piece = (*(Player::board)).get_random_piece(Player::ID);
        //Position of the pawn
        from = (*random_piece).get_pos(); 
        //Now we are going to call the get_possible_moves() on that pawn an then, 
        //randomally, we choose one of the moves
        std::vector<std::string> moves = (*random_piece).get_possible_moves();
        to = moves[rand() % moves.size()];
        (*(Player::board)).move(from, to, Player::ID);
    }
    catch(IllegalMoveException e){
    
        std::cout<<"The move is not allowed, reinsert the values: "<<std::endl;
        Piece* random_piece = (*(Player::board)).get_random_piece(Player::ID);
        //Position of the pawn
        from = (*random_piece).get_pos(); 
        //Now we are going to call the get_possible_moves() on that pawn an then, 
        //randomally, we choose one of the moves
        std::vector<std::string> moves = (*random_piece).get_possible_moves();
        to = moves[rand() % moves.size()];
        (*(Player::board)).move(from, to, Player::ID);
    }

    std::cout<<(*(Player::board))<<std::endl;
    return;
}

#endif  //COMPUTER_CPP