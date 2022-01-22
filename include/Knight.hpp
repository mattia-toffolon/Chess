//Author: Toffolon Mattia

#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"

class Knight : public Piece{

    public:
        // constructs an object "Rook" with the given ID, reference to the Board and initial position
        Knight(const bool& ID, Board* b , std::string arg_pos) : Piece(ID, b, arg_pos) {};
        // checks if the chosen move is valid for this Knight 
        // (in reference to the Board in which it's positioned)
        // can trow an exception if the move is illegal
        bool can_move(const std::string& to) const;
        // writes in the given os stream the characther associated with this Knight
        std::ostream& operator<<(std::ostream& os);
        // returns the characther associated with this Knight
        char to_char();
};

//#include "../src/Knight.cpp"

#endif