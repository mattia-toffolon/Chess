//Francesco Stella 2008816
#ifndef COMPUTER_CPP
#define COMPUTER_CPP
#include "../include/Player.hpp"
#include "../include/Computer.hpp"
#include "../include/Piece.hpp"
#include "../include/DrawException.hpp"
#include <iostream>
#include <vector>
#include <time.h>

//Function that control the turn
void Computer::turn(){
    srand(time(NULL));

    if(board->enough_pieces() == false)
        throw DrawException("Draw: there aren't enough pieces to force a CheckMate");

    if(check==false){
        std::vector<std::pair<std::string, std::string>> safe_moves = get_safe_moves();
        if(safe_moves.size() == 0)
            throw CheckException("Draw: this Player doesn't have any available legal move");

        int i = rand()%(safe_moves.size());
        std::string from = safe_moves[i].first;
        std::string to = safe_moves[i].second;

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
        std::vector<std::pair<std::string, std::string>> escape_moves = get_safe_moves();

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

    return;
}

#endif  //COMPUTER_CPP