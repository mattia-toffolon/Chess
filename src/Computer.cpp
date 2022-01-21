//Francesco Stella 2008816
#ifndef COMPUTER_CPP
#define COMPUTER_CPP
#include "../include/Player.hpp"
#include "../include/Computer.hpp"
#include "../include/Piece.hpp"
#include <iostream>
#include <vector>
#include <time.h>

//Function that control the turn
void Computer::turn(){
    srand(time(NULL));

    if(check==false){
        Piece* random_piece = (*board).get_random_piece(ID);

        while((*random_piece).get_possible_moves().empty())
            random_piece = (*board).get_random_piece(ID);

        std::vector<std::string> moves = (*random_piece).get_possible_moves();
        std::string to = moves[std::rand() % moves.size()];
        std::string from = (*random_piece).get_pos();

        (*board).move(from, to, ID);
    }
    else{
        std::vector<std::pair<std::string, std::string>> escape_moves = get_escape_moves();

        for(std::pair<std::string, std::string> pair : escape_moves){
                std::cout<<pair.first<<"-"<<pair.second<<", ";
        }
        std::cout<<std::endl;

        int i = std::rand()%(escape_moves.size());
        (*board).move(escape_moves[i].first, escape_moves[i].second, ID);
    }

    //std::cout<<(*(board))<<std::endl;
    return;
}

#endif  //COMPUTER_CPP