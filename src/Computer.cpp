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

        if(board->isPromotion(from, to)){
            char prom_chars[] = {'T','C','A','D'};
            int i_p = std::rand()%4;
            (*board).move(from, to, ID, prom_chars[i_p]);
        }
        else
            (*board).move(from, to, ID);

        std::cout<<"Computer move: "<<from<<"-"<<to<<std::endl;
    }
    else{
        std::vector<std::pair<std::string, std::string>> escape_moves = get_escape_moves();

        /*
        for(std::pair<std::string, std::string> pair : escape_moves){
                std::cout<<pair.first<<"-"<<pair.second<<", ";
        }
        std::cout<<std::endl;
        */

        int i_em = std::rand()%(escape_moves.size());
        if(board->isPromotion(escape_moves[i_em].first, escape_moves[i_em].second)){
            char prom_chars[] = {'T','C','A','D'};
            int i_p = std::rand()%4;
            (*board).move(escape_moves[i_em].first, escape_moves[i_em].second, ID, prom_chars[i_p]);
        }
        else
            (*board).move(escape_moves[i_em].first, escape_moves[i_em].second, ID);

        std::cout<<"Computer move: "<<escape_moves[i_em].first<<"-"<<escape_moves[i_em].second<<std::endl;
        check=false;
    }

    //std::cout<<(*(board))<<std::endl;
    return;
}

#endif  //COMPUTER_CPP