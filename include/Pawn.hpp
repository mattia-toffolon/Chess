//Author: Toffolon Mattia

#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece{

    public:
        // constructs an object "Rook" with the given ID, reference to the Board and initial position
        Pawn(bool ID, Board& b, std::string arg_pos) : Piece(ID, b, arg_pos) {};
        // checks if the chosen move is valid for this Pawn 
        // (in reference to the Board in which it's positioned)
        // can trow an exception if the move is illegal or if the match ends
        bool can_move(const std::string& to) const;
        // generates and returns a vector contaning all the possible moves that this Pawn can do as strings 
        // (in reference to the Board in which it's positioned)
        std::vector<std::string> get_possible_moves() const;
        // writes in the given os stream the characther associated with this Pawn
        std::ostream& operator<<(std::ostream& os);
        // returns the characther associated with this Pawn
        char to_char();
};

#include "../src/Pawn.cpp"

#endif