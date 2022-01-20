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
        Piece* random_piece = board->get_random_piece(ID);

        while(random_piece->get_possible_moves().empty())
            random_piece = board->get_random_piece(ID);

        std::vector<std::string> moves = random_piece->get_possible_moves();
        std::string to = moves[std::rand() % moves.size()];
        std::string from = random_piece->get_pos();
        std::string promote = "";
        
        /*
        if(board->isPromotion(from, to){ 
            if(random_piece->getID()==PIECE::BLACK){ 
                std::vector<char> black = {d, a, c, t};
                promote = black[std::rand() % black.size()];
            }
            else{
                std::vector<char> white = {D, A, C, T};
                promote = white[std::rand() % white.size()];
            }
            board->move(from, to, ID, promote);
        }
        else{
            board->move(from, to, ID);  
        }
        */


    std::cout<<(*(board))<<std::endl;
    return;
}

#endif  //COMPUTER_CPP




/*
    bool Board::isPromotion(std::string from, std::string to){

        std::regex pawn_pattern ("[P, p]");
        std::regex coord_pattern ("[A-Ha-h][1,8]");
        if(std::regex_match((*this)[from]->to_char(), pawn_pattern) && (*this)[from]->can_move(to) && std::regex_match(to, coord_pattern)){
            return true;
        }
        return false;
    }
*/

