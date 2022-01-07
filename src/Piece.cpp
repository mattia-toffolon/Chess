#ifndef PIECE_CPP
#define PIECE_CPP

#include"Piece.hpp"

// constructs an object "Piece" with the given ID and the given reference to the Board
Piece::Piece(bool arg_ID, Board& arg_b){
    ID = arg_ID;
    b = &arg_b;
}

// returns a copy of the Piece's ID (that determines its color)
bool Piece::get_ID(){
    return ID;
}

// returns the status of this Piece (true=still on the dashboard, false=eaten)
bool Piece::get_status(){
    return status;
}

// sets the status of this Piece (true=still on the dashboard, false=eaten)
void Piece::set_status(bool arg_status){
    status = arg_status;
}


#endif