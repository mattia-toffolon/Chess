//Author: Toffolon Mattia

#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece{

    private:
        // determines the direction of the moves of this Pawn
        bool direction;
        // determines if the en-passant can be performed on this Pawn or not
        bool en_passant;

    public:
        // constructs an object "Rook" with the given ID, reference to the Board and initial position
        // (en-passant is set to false when to the object is created because to enable the en-passant condition
        // the selected Pawn must have moved by to tiles up or down in one move from its starting position)
        Pawn(const bool& ID, Board* b, std::string arg_pos, bool dir, bool arg_en_passant=false) : Piece(ID, b, arg_pos) {
            en_passant = arg_en_passant;
            direction = dir;
        };
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
        // returns the direction of this Pawn
        bool get_direction();
        // sets en_passant
        void set_en_passant(bool p);
        // returns en_passant
        bool get_en_passant() const;
};

//#include "../src/Pawn.cpp"

#endif