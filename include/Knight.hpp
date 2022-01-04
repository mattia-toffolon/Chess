//Author: Toffolon Mattia

#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"

class Knight : public Piece{

    public:
        // constructs an object "Knight" with the given ID
        Knight(bool ID) : Piece(ID) {};
        // checks if the chosen move is valid for this Knight 
        // (in reference to the Board in which it's positioned)
        // can trow an exception if the move is illegal or if the match ends
        bool can_move(std::string& from, std::string& to);
        // generates and returns a vector contaning all the possible moves that this Knight can do as strings 
        // (in reference to the Board in which it's positioned)
        std::vector<std::string> get_possible_moves(std::string& from);
        // writes in the os stream the characther associated with this Knight
        std::ostream operator<<(std::ostream& os);
        // returns the characther associated with this Knight
        char to_char();
};

#endif