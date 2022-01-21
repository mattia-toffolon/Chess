//Francesco Stella 2008816
#ifndef HUMAN_CPP
#define HUMAN_CPP

#include "../include/Human.hpp"
#include "../include/Board.hpp"
#include "../include/IllegalMoveException.hpp"
#include "../include/CheckException.hpp"
#include <iostream>

void Human::turn(){
    std::string from;
    std::string to;

    if(check==false){
        //asks to Human to insert a pair of tiles until a legal move is inserted
        std::cout<<"Insert the tile in which the chosen Piece is placed and an arrival tile: ";
        while(true){
            std::cin>>from>>to;
            try{
                (*(board)).move(from, to, ID);
                break;
            }
            catch(IllegalMoveException e){
                std::cout<<"The chosen move is not allowed, please reinsert the tiles: ";
            }
        }   
    }
    else{
        // asks to Human to insert the right tiles to escape the check state
        std::cout<<"You are undergoing a check state, choose the right move to free yourself\n";
        std::vector<std::pair<std::string, std::string>> escape_moves = get_escape_moves();
        while(true){
            std::cout<<"Choose between the following escape pairs of tiles:\n";

            for(std::pair<std::string, std::string> pair : escape_moves){
                std::cout<<pair.first<<"-"<<pair.second<<", ";
            }
            std::cout<<std::endl;

            std::cin>>from>>to;
            for(std::pair<std::string, std::string> pair : escape_moves){
                if(from==pair.first && to==pair.second)
                    break;
            }
        }

        (*board).move(from, to, ID);
        check=false;
    }

    //std::cout<<(*(board))<<std::endl;
    return;
}

#endif  //HUMAN_CPP