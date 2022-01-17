//Author: Toffolon Mattia

#ifndef PAWN_CPP
#define PAWN_CPP

#include <iostream>
#include <string>
#include <cmath>

#include "../include/Pawn.hpp"
#include "../include/Board.hpp"

// checks if the chosen move is valid for this Pawn 
// (in reference to the Board in which it's positioned)
// can trow an exception if the move is illegal or if the match ends
bool Pawn::can_move(const std::string& to) const {

    if(to.at(1) - pos.at(1) > 0 && direction != ID || to.at(1) - pos.at(1) < 0 && direction == ID)
        throw IllegalMoveException("The selected move is considered illegal: wrong direction");

    // if the 'to' tile matches the current position of this Piece the move is considered illegal
    if(pos.compare(to)==0)
        throw IllegalMoveException("The selected move is considered illegal. Can't move to the same cell");

    // if the conditions to perfom the en-passant are matched the move is legal
    if(pos.at(1)==to.at(1) && std::abs(pos.at(0)-to.at(0))==1 && (*board)[to]!=nullptr && (*(*board)[to]).get_ID()!=ID && std::toupper((*(*board)[to]).to_char())!='P' ){
        Pawn* p = dynamic_cast<Pawn*>((*board)[to]);
        if((*p).get_en_passant())
            return true;
        else    
            throw IllegalMoveException("The selected move is considered illegal. Can't approach en-passant");
    }

    // case: upper direction
    if(direction){

        std::string mid;
        mid.push_back(to.at(0));
        mid.push_back('3');

        // if the tile in front is free this Pawn can be moved
        if(to.at(1) - pos.at(1) == 1 && (*board)[to]==nullptr)
            return true;

        // if the next two tiles in front are free and this Pawn is in his starting position, it can be moved
        else if(to.at(1)-pos.at(1)==2 && pos.at(1)=='2' && (*board)[to]==nullptr && (*board)[mid]==nullptr)
            return true;

        // if there's an opponent's Piece diagonally and in front of this Pawn, the move is legal
        else if(to.at(1)-pos.at(1)==1 && std::abs(std::toupper(to.at(0))-std::toupper(pos.at(0)))==1 && (*(*board)[to]).get_ID()==(!ID))
            return true;

        // otherwise the selected move is illegal
        else    
            throw IllegalMoveException("The selected move is considered illegal. XD");

    }

    // case: lower direction
    else{

        std::string mid;
        mid.push_back(to.at(0));
        mid.push_back('6');

        // if the tile in front is free this Pawn can be moved
        if(pos.at(1) - to.at(1) == 1 && (*board)[to]==nullptr)
            return true;

        // if the next two tiles in front are free and this Pawn is in his starting position, it can be moved
        else if(pos.at(1)-to.at(1)==2 && pos.at(1)=='7' && (*board)[to]==nullptr && (*board)[mid]==nullptr)
            return true;

        // if there's an opponent's Piece diagonally and in front of this Pawn, the move is legal
        else if(pos.at(1)-to.at(1)==1 && std::abs(std::toupper(to.at(0))-std::toupper(pos.at(0)))==1 && (*(*board)[to]).get_ID()==(!ID))
            return true;

        // otherwise the selected move is illegal
        else    
            throw IllegalMoveException("The selected move is considered illegal.");

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

// sets en_passant
void Pawn::set_en_passant(bool p){
    en_passant = p;
}

// returns en_passant
bool Pawn::get_en_passant() const{
    return en_passant;
}

#endif