//Author: Toffolon Mattia

#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"

class Rook : public Piece{

    public:
        // constructs an object "Rook" with the given ID and the given reference to the Board
        Rook(bool ID, Board& b, std::string arg_pos) : Piece(ID, b, arg_pos) {};
        // checks if the chosen move is valid for this Rook 
        // (in reference to the Board in which it's positioned)
        // can trow an exception if the move is illegal
        bool can_move(std::string& to) const;
        // generates and returns a vector contaning all the possible moves that this Rook can do as strings 
        // (in reference to the Board in which it's positioned)
        std::vector<std::string> get_possible_moves() const;
        // writes in the given os stream the characther associated with this Rook
        std::ostream& operator<<(std::ostream& os);
        // returns the characther associated with this Rook
        char to_char();
};

#endif