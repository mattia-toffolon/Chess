//Author: Toffolon Mattia

#ifndef ROOK_CPP
#define ROOK_CPP

#include <algorithm>
#include <string>
#include "../include/Rook.hpp"
#include "../include/King.hpp"
#include "../include/Board.hpp"

// checks if the chosen move is valid for this Rook 
// (in reference to the Board in which it's positioned)
// can trow an exception if the move is illegal
bool Rook::can_move(const std::string& to) const {

    // if the 'to' tile matches the current position of this Piece the move is considered illegal
    std::string up_to;
    up_to.push_back(std::toupper(to.at(0)));
    up_to.push_back(to.at(1));
    if(pos.compare(up_to)==0)
        throw IllegalMoveException("The selected move is considered illegal: Can't move to the same cell");

    // if the 'to' tile is in a different row and colummn of to 'pos' tile, the move is illegal
    if(std::toupper(pos.at(0))!=std::toupper(to.at(0)) && pos.at(1)!=to.at(1))
        throw IllegalMoveException("The selected move is considered illegal.");

    // if the 'to' tile is occupied by a Piece of this player other than his King (so that the castling can be performed), the move is illegal
    if((*board)[to]!=nullptr && (*(*board)[to]).get_ID()==ID && std::toupper((*(*board)[to]).to_char())!='R' )
        throw IllegalMoveException("The selected move is considered illegal: Can't attack same color");

    // checks the conditions to perform the castling
    if((*board)[to]!=nullptr && (*(*board)[to]).get_ID()==ID && std::toupper((*(*board)[to]).to_char())=='R'){
        King* k = dynamic_cast<King*>((*board)[to]);
        if(get_castling()!=true || (*k).get_castling()!=true)
            throw IllegalMoveException("The selected move is considered illegal: Can't castle due to flags");
        
        for(char i=(char)(std::min((int)pos.at(0),std::toupper(to.at(0))) +1); i<(char)(std::max((int)pos.at(0),std::toupper(to.at(0)))); i++ ){
            std::string p;
            p.push_back(i);
            p.push_back(pos.at(1));
            if((*board)[p] != nullptr || k->is_under_check(p))
                throw IllegalMoveException("The selected move is considered illegal: Can't castle due to pieces or unsafe tiles in between");
        }

        return true;
    }

    // if the 'to' and 'pos' tiles are in the same column, the algorithm checks if the tiles in beetwen are empty.
    // if not, the selected move is illegal
    if(std::toupper(pos.at(0))==std::toupper(to.at(0))){
        for(int i=std::min(pos.at(1), to.at(1))-'1'+2; i<std::max(pos.at(1), to.at(1))-'1'+1; i++ ){
            std::string p;
            p.push_back(pos.at(0));
            p.push_back(i+'0');
            if((*board)[p] != nullptr)
                throw IllegalMoveException("The selected move is considered illegal.");
        }
        return true;
    }

    // otherwise the 'to' and 'pos' tiles must be in the same row, the algorithm checks if the tiles in beetwen are empty.
    // if not, the selected move is illegal
    else{
        for(char i=(char)(std::min((int)std::toupper(pos.at(0)),(int)std::toupper(to.at(0))) +1); i<(char)(std::max((int)std::toupper(pos.at(0)),(int)std::toupper(to.at(0)))); i++ ){
            std::string p;
            p.push_back(i);
            p.push_back(pos.at(1));
            if((*board)[p] != nullptr)
                throw IllegalMoveException("The selected move is considered illegal.");
        }
        return true;
    }
    
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