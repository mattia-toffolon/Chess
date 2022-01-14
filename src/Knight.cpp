//Author: Toffolon Mattia

#ifndef KNIGHT_CPP
#define KNIGHT_CPP

#include <cmath>

#include "../include/Board.hpp"

// checks if the chosen move is valid for this Knight 
// (in reference to the Board in which it's positioned)
// can trow an exception if the move is illegal
bool Knight::can_move(const std::string& to) const{
    
    // if the 'to' tile matches the current position of this Piece the move is considered illegal
    if(pos.compare(to)==0)
        throw IllegalMoveException("The selected move is considered illegal.");

    // if the 'to' tile is occupied by a Piece of this player, the move is illegal
    if((*board)[to]!=nullptr && (*(*board)[to]).get_ID()==ID)
        throw IllegalMoveException("The selected move is considered illegal.");

    // the Knight can move two tiles in one direction and one in the other,
    // if that's not the case the move is illegal
    if(std::abs(pos.at(0)-to.at(0))==2 && std::abs(pos.at(1)-to.at(1))==1)
        return true;
    else if(std::abs(pos.at(0)-to.at(0))==1 && std::abs(pos.at(1)-to.at(1))==2)
        return true;
    else    
        throw IllegalMoveException("The selected move is considered illegal.");

}

// generates and returns a vector contaning all the possible moves that this Knight can do as strings 
// (in reference to the Board in which it's positioned
std::vector<std::string> Knight::get_possible_moves() const{
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

// writes in the os stream the characther associated with this Knight
std::ostream& Knight::operator<<(std::ostream& os){
    os << (ID ? 'c' : 'C');
    return os;
}

// returns the characther associated with this Knight
char Knight::to_char(){
    return (ID ? 'c' : 'C');
}

#endif