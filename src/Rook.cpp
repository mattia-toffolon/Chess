//Author: Toffolon Mattia

#ifndef ROOK_CPP
#define ROOK_CPP

#include <algorithm>

#include "../include/Rook.hpp"
#include "../include/King.hpp"
#include "../include/Board.hpp"

// checks if the chosen move is valid for this Rook 
// (in reference to the Board in which it's positioned)
// can trow an exception if the move is illegal
bool Rook::can_move(const std::string& to) const {

    // if the 'to' tile is in a different row and colummn of to 'pos' tile, the move is illegal
    if(std::toupper(pos.at(0))!=std::toupper(to.at(0)) && pos.at(1)!=to.at(1))
        throw IllegalMoveException("The selected move is considered illegal.");

    // checks the conditions to perform the castling
    if((*(*board)[to]).get_ID()==ID && std::toupper((*(*board)[to]).to_char())=='R'){
        King* k = dynamic_cast<King*>((*board)[to]);
        if(get_castling()!=true || (*k).get_castling()!=true)
            throw IllegalMoveException("The selected move is considered illegal.");
    }

    // if the 'to' tile is occupied by a Piece of this player other than his King (so that the castling can be performed), the move is illegal
    if((*(*board)[to]).get_ID()==ID && std::toupper((*(*board)[to]).to_char())!='R' )
        throw IllegalMoveException("The selected move is considered illegal.");

    // if the 'to' and 'pos' tiles are in the same column, the algorithm checks if the tiles in beetwen are empty.
    // if not, the selected move is illegal
    if(std::toupper(pos.at(0))==std::toupper(to.at(0))){
        for(int i=std::min(pos.at(1), to.at(1))-'1'+1; i<std::max(pos.at(1), to.at(1))-'1'; i++ ){
            std::string p;
            p.push_back(pos.at(0));
            p.push_back(i);
            if((*board)[p] != nullptr)
                throw IllegalMoveException("The selected move is considered illegal.");
        }
        return true;
    }

    // otherwise the 'to' and 'pos' tiles must be in the same column, the algorithm checks if the tiles in beetwen are empty.
    // if not, the selected move is illegal
    else{
        for(char i=(char)(std::min((int)pos.at(0),(int)to.at(0)) +1); i<(char)(std::max((int)pos.at(0),(int)to.at(0))); i++ ){
            std::string p;
            p.push_back(i);
            p.push_back(pos.at(1));
            if((*board)[p] != nullptr)
                throw IllegalMoveException("The selected move is considered illegal.");
        }
        return true;
    }
    
}

// generates and returns a vector contaning all the possible moves that this Rook can do as strings 
// (in reference to the Board in which it's positioned
std::vector<std::string> Rook::get_possible_moves() const {

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

// writes in the os stream the characther associated with this Rook
std::ostream& Rook::operator<<(std::ostream& os){
    os << (ID ? 't' : 'T');
    return os;
}

// returns the characther associated with this Rook
char Rook::to_char(){
    return (ID ? 't' : 'T');
}

// sets castling
void Rook::set_castling(bool c){
    castling = c;
}

// returns castling
bool Rook::get_castling() const{
    return castling;
}

#endif