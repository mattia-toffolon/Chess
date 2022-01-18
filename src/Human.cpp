//Francesco Stella 2008816
#ifndef HUMAN_CPP
#define HUMAN_CPP
#include "../include/Player.hpp"
#include "../include/Human.hpp"
#include "../include/Board.hpp"
#include "../include/IllegalMoveException.hpp"
#include <iostream>

void Human::turn(){
    std::string from = "";
    std::string to = "";
    std::cout<<"Insert the box where is the piece to move and the box of arrival:"<<std::endl;
    std::cin>>from>>to;
    try{
        (*(board)).move(from, to, ID);
    }
    catch(IllegalMoveException e){
        std::cout<<"The move is not allowed, reinsert the tiles: "<<std::endl;
        std::cin>>from>>to;
        (*(board)).move(from, to, ID);
    }

    std::cout<<(*(board))<<std::endl;
    return;
}

#endif  //HUMAN_CPP