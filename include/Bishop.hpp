//Author: Toffolon Mattia

#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"

class Bishop : public Piece{

    public:
        // constructs an object "Bishop" with the given ID
        Bishop(bool ID) : Piece(ID) {};
        // checks if the chosen move is valid for this Bishop 
        // (in reference to the Board in which it's positioned )
        bool can_move(std::string& from, std::string& to);
        // generates and returns a vector contaning all the possible moves that this Bishop can do as strings 
        // (in reference to the Board in which it's positioned)
        std::vector<std::string> get_possible_moves(std::string& from);
        // writes in the os stream the characther associated with this Bishop
        std::ostream operator<<(std::ostream& os);
        // returns the characther associated with this Bishop
        char to_char();
};

#endif