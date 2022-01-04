// Author: Toffolon Mattia

#ifndef PIECE_HPP
#define PIECE_HPP

#include<iostream>
#include<vector>
#include"Board.hpp"

class Piece {

    private:
        // specifies the color of the Piece (true=WHITE, false=BLACK)
        bool ID;
        // specifies if the Piece is still on the dashboard or if it has been eaten
        bool status;
        // pointer to the dashboard in which the Piece is positioned
        Board* b;

    public:
        // expressions that identify the colors WHITE and BLACK as bool variables (respectivly true and false)
        static constexpr bool WHITE = true;
        static constexpr bool BLACK = false;
        // checks if the chosen move is valid for the Piece 
        // (also in reference to the Board in which it's positioned )
        virtual bool can_move(std::string& from, std::string& to) = 0;
        // generates e returns a vector contaning all the possible moves that the Piece can do as strings 
        // (also in reference to the Board in which it's positioned )
        virtual std::vector<std::string> get_possible_moves(std::string& from) = 0;
        // writes in the os stream the characther associated with the Piece
        virtual std::ostream operator<<(std::ostream& os) = 0;
        // returns a copy of the Piece's ID (that determines its color)
        bool get_ID();
        // return the characther associated with the Piece
        char to_char();

};

#endif