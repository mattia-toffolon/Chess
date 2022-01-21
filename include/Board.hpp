// Author: Guerrini Alberto

#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

#include "IllegalMoveException.hpp"
#include "Logger.hpp"
#include "Piece.hpp"

class Pawn;

class Board {
    private:
        // contains references to all pieces:
        // [0,7] white pawn, [8,15] white other pieces (in the order from left to right in the board)
        // [16,23] white pawn, [24,31] white other pieces (in the order from left to right in the board)
        std::vector<Piece*> pieces_;
        // represents the dashboard, it starts having in the first rows the pieces of the player
        std::vector<std::vector<Piece*>> dashboard_;
        // for logging all the moves made in a file
        Logger logger_;
        
    public:
        static constexpr short DIM = 8;
        // index offset to reach the first black piece in the pieces_ vector
        static constexpr short COLOR_OFFSET = 16;
        explicit Board(const bool& player_color);
        Board (Board& arg);
        ~Board();
        // moves the piece in the cell identified by the coordinates "from" to the one identified
        // by the coordinates "to". Can trow an exception if the move is illegal or if the match ends
        // promote if setted should be uppercase and specifies the promotion requested for the moved piece
        bool move(const std::string& from, const std::string& to, const bool player_ID, const char promote = 'N');
        // check if the chosen move is a promotion
        bool isPromotion(const std::string& from, const std::string& to);
        // returns a reference to the piece at i position of the specified color in the pieces array
        // returns nullptr if the piece has been captured
        // i must be in [0,15], the pieces are P P P P P P P P T C A D R A C T
        Piece* get_piece_at(const int i, const bool ID) const;
        // returns a reference to a random piece of the specified color
        Piece* get_random_piece(const bool ID);
        // returns the reference to the pointer to the piece in the position identified
        // by the coordinates coord. Returns a reference to null if there isn't pieces
        // Can trow std::invalid_argoument if coordinates aren't in [A-Ha-h][1-8] format
        Piece*& operator[](const std::string& coord);

    private:
        // implements the capture of one piece
        bool capture(const std::string& from, const std::string& to);
        // implements the castling move
        bool castling(const std::string& from, const std::string& to, const bool player_ID);
        // implements promotion operation
        bool promote(const std::string& piece_pos, const bool player_ID, const char promotion);
};

// writes in the os stream the dashboard as a square using letters to identify pieces
std::ostream& operator<<(std::ostream& os, Board& b);

#endif