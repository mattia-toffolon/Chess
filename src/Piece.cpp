//Author: Toffolon Mattia

#ifndef PIECE_CPP
#define PIECE_CPP

#include "../include/Piece.hpp"

constexpr bool Piece::WHITE;
constexpr bool Piece::BLACK;

// constructs an object "Piece" with the given ID and the given reference to the Board
// (when a new Piece is created, status is automatically set to true beacuse we assume 
// that it will be instantly placed on the dashboard)
Piece::Piece(const bool& arg_ID, Board* arg_board, std::string arg_pos){
    ID = arg_ID;
    board = arg_board;
    pos = arg_pos;
}

// generates and returns a vector contaning all the possible moves that this Bishop can do as strings 
// (in reference to the Board in which it's positioned
std::vector<std::string> Piece::get_possible_moves() const {
    // scans all tiles of dashboard in search of possible moves
    std::vector<std::string> ret;
    for(char i = 'A'; i<='H'; i++){
        for(int j=1; j<=8; j++){
            std::string to;
            to.push_back(i);
            to.push_back(j+'0');
            try{
                if(can_move(to))
                ret.push_back(to);
            }
            catch(IllegalMoveException e){
                continue;
            }
            
        }
    }
    return ret;
}

// returns a copy of the Piece's ID (that determines its color)
bool Piece::get_ID(){
    return ID;
}

// returns the string that determines the position of this Piece on the dashboard
std::string Piece::get_pos(){
    return pos;
}

// sets the string that determines the position of this Piece on the dashboard
void Piece::set_pos(std::string arg_pos){
    pos = arg_pos;
}

#endif