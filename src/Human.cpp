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
                if(board->isPromotion(from, to)){
                    std::cout<<"You are promoting one of your Pawns, choose a Piece to procede: ";
                    std::string prom;
                    std::cin>>prom;
                    std::cout<<std::endl;
                    std::regex prom_pattern("[t,T,c,C,a,A,d,D]");
                    if(prom.size()!=1 || !std::regex_match(prom, prom_pattern)){
                        std::cout<<"Input not valid, please choose again a move: ";
                        continue;
                    }
                    is_safe_move(from, to, prom.at(0));
                    (*board).move(from, to, ID, prom.at(0));
                    break;
                }
                else{
                    is_safe_move(from, to);
                    (*board).move(from, to, ID);
                    break;
                }
            }
            catch(IllegalMoveException e){
                std::cout<<e.what()<<std::endl;
                std::cout<<"Please reinsert the tiles: ";
                continue;
            }
        }   
    }
    else{
        // asks to Human to insert the right tiles to escape the check state
        std::cout<<"You are undergoing a check state, choose the right move to free yourself\n";
        std::vector<std::pair<std::string, std::string>> escape_moves = get_escape_moves();
        while(true){
            std::cout<<"Choose between the following pairs of escape-tiles:\n";

            for(std::pair<std::string, std::string> pair : escape_moves){
                std::cout<<pair.first<<"-"<<pair.second<<"  ";
            }
            std::cout<<"->  ";

            std::cin>>from>>to;
            for(std::pair<std::string, std::string> pair : escape_moves){
                if(std::toupper(from.at(0))==pair.first.at(0) && from.at(1)==pair.first.at(1) && std::toupper(to.at(0))==pair.second.at(0) && to.at(1)==pair.second.at(1)){
                    //from.compare(pair.first)==0 && to.compare(pair.second)==0){
                    if(board->isPromotion(from, to)){
                        std::cout<<"You are promoting one of your Pawns, choose a Piece to procede: ";
                        std::string prom;
                        std::cin>>prom;
                        std::cout<<std::endl;
                        std::regex prom_pattern("[t,T,c,C,a,A,d,D]");
                        if(prom.size()!=1 || !std::regex_match(prom, prom_pattern)){
                            std::cout<<"Input not valid, please choose again a move: ";
                            continue;
                        }
                        (*board).move(from, to, ID, prom.at(0));
                    }
                    else{
                        (*board).move(from, to, ID);
                    }
                    check=false;
                    return;
                }
            }
        }
    }

    //std::cout<<(*(board))<<std::endl;
    return;
}

#endif  //HUMAN_CPP