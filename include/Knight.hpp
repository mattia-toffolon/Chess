//Author: Toffolon Mattia

#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"

class Knight : public Piece{

    public:
        // constructs an object "Rook" with the given ID, reference to the Board and initial position
        Knight(bool ID, Board& b , std::string arg_pos) : Piece(ID, b, arg_pos) {};
        // checks if the chosen move is valid for this Knight 
        // (in reference to the Board in which it's positioned)
        // can trow an exception if the move is illegal
        bool can_move(std::string& to) const;
        // generates and returns a vector contaning all the possible moves that this Knight can do as strings 
        // (in reference to the Board in which it's positioned)
        std::vector<std::string> get_possible_moves() const;
        // writes in the given os stream the characther associated with this Knight
        std::ostream& operator<<(std::ostream& os);
        // returns the characther associated with this Knight
        char to_char();
};

#endif