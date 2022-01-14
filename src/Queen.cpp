// Author: Toffolon Mattia

#ifndef QUEEN_CPP
#define QUEEN_CPP

#include <algorithm>
#include <cmath>

#include "../include/Board.hpp"

// checks if the chosen move is valid for this Queen 
// (in reference to the Board in which it's positioned)
// can trow an exception if the move is illegal
bool Queen::can_move(const std::string& to) const{

    // if the 'to' tile matches the current position of this Piece the move is considered illegal
    if(pos.compare(to)==0)
        throw IllegalMoveException("The selected move is considered illegal.");

    // if the 'to' tile is occupied by a Piece of this player, the move is illegal
    if((*board)[to]!=nullptr && (*(*board)[to]).get_ID()==ID)
        throw IllegalMoveException("The selected move is considered illegal.");

    // if this move can neither be perfomed by a Rook nor a Bishop, the move illegal
    if((std::toupper(pos.at(0))!=std::toupper(to.at(0)) && pos.at(1)!=to.at(1)) && (std::abs(pos.at(0)-to.at(0)) != std::abs(pos.at(1)-to.at(1))))
        throw IllegalMoveException("The selected move is considered illegal.");

    // case: this Queen is moving up to the right or down to the left
    // the algorithm checks if the tiles in beetwen are empty. If not, the selected move is illegal
    if( (pos.at(0)>to.at(0)&&(pos.at(1)>to.at(1))) || (pos.at(0)<to.at(0)&&(pos.at(1)<to.at(1))) ){
        char i=((char)std::min(pos.at(0), to.at(0)))+1;
        char j=((char)std::min(pos.at(1), to.at(1)))+1;
        while(i!=std::max(pos.at(0), to.at(0)) && j!=std::max(pos.at(1), to.at(1))){
            std::string p;
            p.push_back(i);
            p.push_back(j);
            if((*board)[p] != nullptr)
                throw IllegalMoveException("The selected move is considered illegal.");
            
            i = i+1;
            j = j+1;
        }
        return true;
    }
    // case: this Queen is moving up to the right or down to the left
    // the algorithm checks if the tiles in beetwen are empty. If not, the selected move is illegal   
    else if( (pos.at(0)>to.at(0)&&(pos.at(1)<to.at(1))) || (pos.at(0)<to.at(0)&&(pos.at(1)>to.at(1))) ){
        char i=((char)std::min(pos.at(0), to.at(0)))+1;
        char j=((char)std::max(pos.at(1), to.at(1)))+1;
        while(i!=std::max(pos.at(0), to.at(0)) && j!=std::min(pos.at(1), to.at(1))){
            std::string p;
            p.push_back(i);
            p.push_back(j);
            if((*board)[p] != nullptr)
                throw IllegalMoveException("The selected move is considered illegal.");
            
            i = i+1;
            j = j-1;
        }
        return true;
    }
    // case: this Queen is moving straight up or down
    // the algorithm checks if the tiles in beetwen are empty. If not, the selected move is illegal
    else if(std::toupper(pos.at(0))==std::toupper(to.at(0))){
        for(int i=std::min(pos.at(1), to.at(1))-'1'+1; i<std::max(pos.at(1), to.at(1))-'1'; i++ ){
            std::string p;
            p.push_back(pos.at(0));
            p.push_back(i);
            if((*board)[p] != nullptr)
                throw IllegalMoveException("The selected move is considered illegal.");
        }
        return true;
    }
    // case: this Queen is moving straight to the right or to the left
    // the algorithm checks if the tiles in beetwen are empty. If not, the selected move is illegal
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

// generates and returns a vector contaning all the possible moves that this Queen can do as strings 
// (in reference to the Board in which it's positioned
std::vector<std::string> Queen::get_possible_moves() const {

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

// writes in the os stream the characther associated with this Queen
std::ostream& Queen::operator<<(std::ostream& os){
    os << (ID ? 'd' : 'D');
    return os;
}

// returns the characther associated with this Queen
char Queen::to_char(){
    return (ID ? 'd' : 'D');
}

#endif