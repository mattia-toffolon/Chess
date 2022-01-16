//Author: Toffolon Mattia

#ifndef KING_CPP
#define KING_CPP

#include "../include/King.hpp"
#include "../include/Rook.hpp"
#include "../include/Board.hpp"

// checks if the chosen move is valid for this King 
// (in reference to the Board in which it's positioned)
// can trow an exception if the move is illegal or if the match ends
bool King::can_move(const std::string& to) const {

    // if the 'to' tile matches the current position of this Piece the move is considered illegal
    if(pos.compare(to)==0)
        throw IllegalMoveException("The selected move is considered illegal.");

    // if the 'to' tile is occupied by a Piece of this player other than one of his Rooks (so that the castling can be performed), the move is illegal
    if((*board)[to]!=nullptr && (*(*board)[to]).get_ID()==ID && std::toupper((*(*board)[to]).to_char())!='T' )
        throw IllegalMoveException("The selected move is considered illegal.");

    // checks the conditions to perform the castling
    if((*(*board)[to]).get_ID()==ID && std::toupper((*(*board)[to]).to_char())=='T'){
        Rook* t = dynamic_cast<Rook*>((*board)[to]);
        if(get_castling()!=true || (*t).get_castling()!=true)
            throw IllegalMoveException("The selected move is considered illegal.");

        for(char i=(char)(std::min((int)pos.at(0),(int)to.at(0)) +1); i<(char)(std::max((int)pos.at(0),(int)to.at(0))); i++ ){
            std::string p;
            p.push_back(i);
            p.push_back(pos.at(1));
            if((*board)[p] != nullptr)
                throw IllegalMoveException("The selected move is considered illegal.");
        }

        return true;
    }

    // if the absolute values of the both differences between the x and y coordinates of the 'pos' tile and the 'to' tile are <=1 
    // and the 'to' tile is empty or there's an opponent's Piece in it, the move is valid
    if(std::abs(std::toupper(to.at(0))-std::toupper(pos.at(0)))<=1 && std::abs(to.at(1)-pos.at(1))<=1 && (((*board)[to]==nullptr) || (*(*board)[to]).get_ID()!=ID) )
        return true;

    // otherwise the selected move is illegal
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