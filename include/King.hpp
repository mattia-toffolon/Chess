//Author: Toffolon Mattia

#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece{

    public:
        // checks if the chosen move is valid for this King 
        // (also in reference to the Board in which it's positioned )
        bool can_move(std::string& from, std::string& to);
        // generates and returns a vector contaning all the possible moves that this King can do as strings 
        // (also in reference to the Board in which it's positioned)
        std::vector<std::string> get_possible_moves(std::string& from);
        // writes in the os stream the characther associated with this King
        std::ostream operator<<(std::ostream& os);
        // returns the characther associated with this King
        char to_char();
};

#endif