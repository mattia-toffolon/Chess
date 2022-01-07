//Author: Toffolon Mattia

#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"

class Rook : public Piece{

    public:
        // constructs an object "Rook" with the given ID
        Rook(bool ID, Board& b) : Piece(ID, b) {};
        // checks if the chosen move is valid for this Rook 
        // (in reference to the Board in which it's positioned)
        // can trow an exception if the move is illegal or if the match ends
        bool can_move(std::string& from, std::string& to) const;
        // generates and returns a vector contaning all the possible moves that this Rook can do as strings 
        // (in reference to the Board in which it's positioned)
        std::vector<std::string> get_possible_moves(std::string& from) const;
        // writes in the os stream the characther associated with this Rook
        std::ostream operator<<(std::ostream& os);
        // returns the characther associated with this Rook
        char to_char();
};

#endif