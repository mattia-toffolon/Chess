//Author: Toffolon Mattia

#ifndef KING_CPP
#define KING_CPP

#include"../include/King.hpp"

// checks if the chosen move is valid for this King 
// (in reference to the Board in which it's positioned)
// can trow an exception if the move is illegal or if the match ends
bool King::can_move(std::string& to) const {

    // if the absolute values of the both differences between the x and y coordinates of the 'pos' tile and the 'to' tile are <=1 
    // and the 'to' tile is empty or there's an opponent's Piece in it, the move is valid
    if(std::abs(std::toupper(to.at(0))-std::toupper(pos.at(0)))<=1 && std::abs(to.at(1)-pos.at(1))<=1 && (((*board)[to]==nullptr) || (*(*board)[to]).get_ID()!=ID) )
        return true;

    // otherwise the selected move is unexcecutable
    else
        throw IllegalMoveException("The selected move is considered illegal.");
}

// generates and returns a vector contaning all the possible moves that this King can do as strings 
// (in reference to the Board in which it's positioned
std::vector<std::string> King::get_possible_moves() const{
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

// writes in the os stream the characther associated with this King
std::ostream& King::operator<<(std::ostream& os){
    os << (ID ? 'r' : 'R');
    return os;
}

// returns the characther associated with this King
char King::to_char(){
    return (ID ? 'r' : 'R');
}

// sets castling
void King::set_castling(bool c){
    castling = c;
}

// returns castling
bool King::get_castling() const{
    return castling;
}


#endif