// Author: Toffolon Mattia

#ifndef PIECE_HPP
#define PIECE_HPP

#include<iostream>
#include<vector>

// #include"Board.hpp"
#include"IllegalMoveException.hpp"

class Board;

class Piece {

    protected:
        // specifies the color of the Piece (true=WHITE, false=BLACK)
        bool ID;
        // specifies if the Piece is still on the dashboard or if it has been eaten
        bool status;
        // string that determines the position of this Piece on the dashboard
        std::string pos;
        // pointer to the dashboard in which the Piece is positioned
        Board* board;

    public:
        // expressions that identify the colors WHITE and BLACK as bool variables (respectivly true and false)
        static constexpr bool WHITE = true;
        static constexpr bool BLACK = false;
        // constructs an object "Rook" with the given ID, reference to the Board and initial position
        Piece(const bool& arg_ID, Board* arg_board, std::string arg_pos);
        // checks if the chosen move is valid for this Piece 
        // (in reference to the Board in which it's positioned)
        // can trow an exception if the move is illegal
        virtual bool can_move(const std::string& to) const = 0;
        // generates and returns a vector contaning all the possible moves that this Piece can do as strings 
        // (in reference to the Board in which it's positioned)
        virtual std::vector<std::string> get_possible_moves() const = 0;
        // writes in the given os stream the characther associated with this Piece
        virtual std::ostream& operator<<(std::ostream& os) = 0;
        // returns a copy of the Piece's ID (that determines its color)
        bool get_ID();
        // return the characther associated with this Piece
        virtual char to_char() = 0;
        // returns the status of this Piece (true=still on the dashboard, false=eaten)
        bool get_status();
        // sets the status of this Piece (true=still on the dashboard, false=eaten)
        void set_status(bool status);
        // returns the string that determines the position of this Piece on the dashboard
        std::string get_pos();
        // sets the string that determines the position of this Piece on the dashboard
        void set_pos(std::string arg_pos);
        // invalidates copy constructor and copy assignement for "Piece" objects to avoid slicing 
        Piece(Piece&) = delete;
        Piece& operator=(Piece&) = delete;

};

#include"../src/Piece.cpp"

#endif