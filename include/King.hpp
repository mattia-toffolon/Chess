//Author: Toffolon Mattia

#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece{

    private:
        // determines if the castling can be performed or not
        bool castling;

    public:
        // constructs an object "Rook" with the given ID, reference to the Board and initial position
        // (castling is set to true when the Rook is placed in the dashboard since castling can be 
        // performed only if both the selected Rook and the King haven't moved yet)
        King(const bool& ID, Board* b, std::string arg_pos, bool arg_castling=true) : Piece(ID, b, arg_pos) {
            castling=arg_castling;
        };
        // checks if the chosen move is valid for this King 
        // (in reference to the Board in which it's positioned)
        // can trow an exception if the move is illegal or if the match ends
        bool can_move(const std::string& to) const;
        // generates and returns a vector contaning all the possible moves that this King can do as strings 
        // (in reference to the Board in which it's positioned)
        std::vector<std::string> get_possible_moves() const;
        // writes in the given os stream the characther associated with this King
        std::ostream& operator<<(std::ostream& os);
        // returns the characther associated with this King
        char to_char();
        // sets castling
        void set_castling(bool c);
        // returns castling
        bool get_castling() const;
        // tells if this King is under Check
        bool is_under_check(std::string tile) const;
};

//#include "../src/King.cpp"

#endif