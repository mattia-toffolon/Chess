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
        Piece* random_piece = (*board).get_random_piece(ID);

        while((*random_piece).get_possible_moves().empty())
            random_piece = (*board).get_random_piece(ID);

        std::vector<std::string> moves = (*random_piece).get_possible_moves();
        std::string to = moves[std::rand() % moves.size()];
        std::string from = (*random_piece).get_pos();

        (*board).move(from, to, ID);

    std::cout<<(*(board))<<std::endl;
    return;
}

#endif  //COMPUTER_CPP