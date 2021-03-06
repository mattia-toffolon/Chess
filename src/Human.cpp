//Francesco Stella 2008816
#ifndef HUMAN_CPP
#define HUMAN_CPP

#include "../include/Human.hpp"
#include "../include/Board.hpp"
#include "../include/IllegalMoveException.hpp"
#include "../include/CheckException.hpp"
#include "../include/DrawException.hpp"
#include <iostream>

void Human::turn(){
    std::string from;
    std::string to;

    //if the combination of active pieces isn't enough to force a CheckMate then it's a Draw
    if(board->enough_pieces() == false)
        throw DrawException("Draw: there aren't enough pieces to force a CheckMate");

    if(check==false){
        if(get_safe_moves().size() == 0)
            throw DrawException("Draw: this Player doesn't have any available safe move without being under Check");

        //asks to Human to insert a pair of tiles until a legal move is inserted
        //if "pp pp" is inserted then Human asks to Computer to end the Match with a tie (Computer always accepts)
        //if "xx xx" is inserted then the Board gets printed in std::ostream
        std::cout<<"Insert the tile in which the chosen Piece is placed and an arrival tile: ";
        while(true){
            std::cin>>from>>to;
            if(from.size()!=2 || to.size()!=2){
                std::cout<<"Wrong format. Please reinsert the tiles: ";
                continue;
            }

            if(std::toupper(from.at(0))=='P' && std::toupper(from.at(1))=='P' && std::toupper(to.at(0))=='P' && std::toupper(to.at(1))=='P')
                throw DrawException("Draw: players agreed for a tie");

            if(std::toupper(from.at(0))=='X' && std::toupper(from.at(1))=='X' && std::toupper(to.at(0))=='X' && std::toupper(to.at(1))=='X'){
                std::cout<<(*board)<<std::endl;
                std::cout<<"Insert the tile in which the chosen Piece is placed and an arrival tile: ";
                continue;
            }

            try{
                //checks is the selected move implies Promotion
                //if yes, asks Human to insert a char corrisponding to the chosen new Piece
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
                //if the selected move is illegal, Human has to reinsert a pair of tiles
                std::cout<<e.what()<<std::endl;
                std::cout<<"Please reinsert the tiles: ";
                continue;
            }
        }   
    }
    else{
        // asks to Human to insert the right tiles to escape the check state
        std::cout<<"You are undergoing a check state, choose the right move to free yourself\n";
        std::vector<std::pair<std::string, std::string>> escape_moves = get_safe_moves();
        while(true){
            std::cout<<"Choose between the following pairs of escape-tiles:\n";

            for(std::pair<std::string, std::string> pair : escape_moves){
                std::cout<<pair.first<<"-"<<pair.second<<"  ";
            }
            std::cout<<"->  ";

            std::cin>>from>>to;

            if(from.size()!=2 || to.size()!=2){
                std::cout<<"Wrong format\n";
                continue;
            }

            if(std::toupper(from.at(0))=='X' && std::toupper(from.at(1))=='X' && std::toupper(to.at(0))=='X' && std::toupper(to.at(1))=='X'){
                std::cout<<(*board)<<std::endl;
                continue;
            }

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

    return;
}

#endif  //HUMAN_CPP