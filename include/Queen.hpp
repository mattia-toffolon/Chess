//Author: Toffolon Mattia

#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"

class Queen : public Piece{

    public:
        // constructs an object "Queen" with the given ID and the given reference to the Board
        Queen(bool ID, Board& b) : Piece(ID, b) {};
        // checks if the chosen move is valid for this Queen 
        // (in reference to the Board in which it's positioned)
        // can trow an exception if the move is illegal or if the match ends
        bool can_move(std::string& from, std::string& to) const;
        // generates and returns a vector contaning all the possible moves that this Queen can do as strings 
        // (in reference to the Board in which it's positioned)
        std::vector<std::string> get_possible_moves(std::string& from) const;
        // writes in the given os stream the characther associated with this Queen
        std::ostream& operator<<(std::ostream& os);
        // returns the characther associated with this Queen
        char to_char();
};

#endif