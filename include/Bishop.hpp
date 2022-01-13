//Author: Toffolon Mattia

#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"

class Bishop : public Piece{

    public:
        // constructs an object "Rook" with the given ID, reference to the Board and initial position
        Bishop(const bool& ID, Board* b, std::string arg_pos) : Piece(ID, b, arg_pos) {};
        // checks if the chosen move is valid for this Bishop 
        // (in reference to the Board in which it's positioned)
        // can trow an exception if the move is illegal
        bool can_move(const std::string& to) const;
        // generates and returns a vector contaning all the possible moves that this Bishop can do as strings 
        // (in reference to the Board in which it's positioned)
        std::vector<std::string> get_possible_moves() const;
        // writes in the given os stream the characther associated with this Bishop
        std::ostream& operator<<(std::ostream& os);
        // returns the characther associated with this Bishop
        char to_char();
};

#endif