//Author: Toffolon Mattia

#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"

class Queen : public Piece{

    public:
        // constructs an object "Rook" with the given ID, reference to the Board and initial position
        Queen(const bool& ID, Board* b, std::string arg_pos) : Piece(ID, b, arg_pos) {};
        // checks if the chosen move is valid for this Queen 
        // (in reference to the Board in which it's positioned)
        // can trow an exception if the move is illegal
        bool can_move(const std::string& to) const;
        // generates and returns a vector contaning all the possible moves that this Queen can do as strings 
        // (in reference to the Board in which it's positioned)
        std::vector<std::string> get_possible_moves() const;
        // writes in the given os stream the characther associated with this Queen
        std::ostream& operator<<(std::ostream& os);
        // returns the characther associated with this Queen
        char to_char();
};

#include "../src/Queen.cpp"

#endif