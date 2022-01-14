//Author: Toffolon Mattia

#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"

class Rook : public Piece{

    private:
        // determines if the castling can be performed or not
        bool castling;

    public:
        // constructs an object "Rook" with the given ID, reference to the Board and initial position
        // (castling is set to true when the Rook is placed in the dashboard since castling can be 
        // performed only if both the selected Rook and the King haven't moved yet)
        Rook(const bool& ID, Board* b, std::string arg_pos) : Piece(ID, b, arg_pos) {castling=true;};
        // checks if the chosen move is valid for this Rook 
        // (in reference to the Board in which it's positioned)
        // can trow an exception if the move is illegal
        bool can_move(const std::string& to) const;
        // generates and returns a vector contaning all the possible moves that this Rook can do as strings 
        // (in reference to the Board in which it's positioned)
        std::vector<std::string> get_possible_moves() const;
        // writes in the given os stream the characther associated with this Rook
        std::ostream& operator<<(std::ostream& os);
        // returns the characther associated with this Rook
        char to_char();
        // sets castling
        void set_castling(bool c);
        // returns castling
        bool get_castling() const;
};

#include "../src/Rook.cpp"

#endif