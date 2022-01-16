//Author: Toffolon Mattia

#ifndef PIECE_CPP
#define PIECE_CPP

constexpr bool Piece::WHITE;
constexpr bool Piece::BLACK;

// constructs an object "Piece" with the given ID and the given reference to the Board
// (when a new Piece is created, status is automatically set to true beacuse we assume 
// that it will be instantly placed on the dashboard)
Piece::Piece(const bool& arg_ID, Board* arg_board, std::string arg_pos){
    ID = arg_ID;
    board = arg_board;
    pos = arg_pos;
    status = true;
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

// returns the string that determines the position of this Piece on the dashboard
std::string Piece::get_pos(){
    return pos;
}

// sets the string that determines the position of this Piece on the dashboard
void Piece::set_pos(std::string arg_pos){
    pos = arg_pos;
}

#endif