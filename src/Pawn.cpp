//Author: Toffolon Mattia

#ifndef PAWN_CPP
#define PAWN_CPP

#include <iostream>
#include <string>
#include <cmath>

#include "../include/Pawn.hpp"

// checks if the chosen move is valid for this Pawn 
// (in reference to the Board in which it's positioned)
// can trow an exception if the move is illegal or if the match ends
bool Pawn::can_move(const std::string& to) const {

    // case: white Pawn
    if( (*(*board)[pos]).get_ID() ){

        // if the tile in front is free this Pawn can be moved
        if(to.at(1) - pos.at(1) == 1 && (*board)[to]==nullptr)
            return true;

        // if the next two tiles in front are free and this Pawn is in his starting position, it can be moved
        else if(to.at(1)-pos.at(1)==2 && to.at(1)==2 && (*board)[to]==nullptr && (*board)[to.at(0)+"3"]==nullptr)
            return true;

        // if there's an opponent's Piece diagonally and in front of this Pawn, the move can be executed
        else if(to.at(1)-pos.at(1)==1 && std::abs(std::toupper(to.at(0))-std::toupper(pos.at(0)))==1 && (*(*board)[to]).get_ID()==Piece::BLACK)
            return true;

        // otherwise the selected move is unexecutable
        else    
            throw IllegalMoveException("The selected move is considered illegal.");

        // --- DA IMPLEMENTARE: EN PASSANT!
    }

    // case: black Pawn
    else{

        // if the tile in front is free this Pawn can be moved
        if(pos.at(1) - to.at(1) == 1 && (*board)[to]==nullptr)
            return true;

        // if the next two tiles in front are free and this Pawn is in his starting position, it can be moved
        else if(pos.at(1)-to.at(1)==2 && to.at(1)==7 && (*board)[to]==nullptr && (*board)[to.at(0)+"6"]==nullptr)
            return true;

        // if there's an opponent's Piece diagonally and in front of this Pawn, the move can be executed
        else if(pos.at(1)-to.at(1)==1 && std::abs(std::toupper(to.at(0))-std::toupper(pos.at(0)))==1 && (*(*board)[to]).get_ID()==Piece::WHITE)
            return true;

        // otherwise the selected move is unexecutable
        else    
            throw IllegalMoveException("The selected move is considered illegal.");

        // --- DA IMPLEMENTARE: EN PASSANT!

    }

}

// generates and returns a vector contaning all the possible moves that this Pawn can do as strings 
// (in reference to the Board in which it's positioned
std::vector<std::string> Pawn::get_possible_moves() const {

    // scans all tiles of dashboard in search of possible moves
    std::vector<std::string> ret;
    for(char i = 'A'; i<='H'; i++){
        for(int j=1; j<=8; j++){
            std::string to;
            to.push_back(i);
            to.push_back(j);
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

    // --- E' POSSIBILE RENDERLO PIU' EFFICIENTE

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