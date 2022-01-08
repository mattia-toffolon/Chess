#ifndef PAWN_CPP
#define PAWN_CPP

#include <iostream>
#include "include/Pawn.hpp"

// checks if the chosen move is valid for this Pawn 
// (in reference to the Board in which it's positioned)
// can trow an exception if the move is illegal or if the match ends
bool Pawn::can_move(std::string& from, std::string& to) const {

    int i = (isupper(from.at(0)) ? from.at(0)-'A' : from.at(0)-'a');
    i = (from.at(1)-1)*Board::DIM + i;

    //DA CONTINUARE
}

// writes in the os stream the characther associated with this Pawn
std::ostream& Pawn::operator<<(std::ostream& os){
    os << (ID ? 'p' : 'P');
    return os;
}

// returns the characther associated with this Pawn
char Pawn::to_char(){
    return (ID ? 'p' : 'P');
}

#endif