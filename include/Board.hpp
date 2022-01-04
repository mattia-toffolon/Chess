// Author: Guerrini Alberto

#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include "Piece.hpp"

class Board {
    
    private:
        static constexpr short DIM = 8;
        // index offset to reach the first black piece in the pieces_ vector
        static constexpr short COLOR_OFFSET = 16;
        // contains references to all pieces:
        // [0,7] white pawn, [8,15] white other pieces (in the order from left to right in the board)
        // [16,23] white pawn, [24,31] white other pieces (in the order from left to right in the board)
        std::vector<Piece*> pieces_;
        // represents the dashboard, it starts having in the first rows the pieces of the player
        std::vector<std::vector<Piece*>> dashboard_;

    public:
        explicit Board(bool player_color = Piece::WHITE);
        // moves the piece in the cell identified by the coordinates "from" to the one identified
        // by the coordinates "to". Can trow an exception if the move is illegal or if the match ends
        bool move(const std::string& from, const std::string& to);
        // returns a reference to the piece at i position with the specified color in the pieces array
        // i must be in [0,15], the pieces are P P P P P P P P T C A D R A C T
        Piece& get_piece(const int i, const bool ID);
        // writes in the os stream the dashboard as a square using letters to identify pieces
        std::ostream& operator<<(std::ostream& os) const;
        // returns the reference to the pointer to the piece in the position identified
        // by the coordinates coord. Returns a reference to null if there isn't pieces
        Piece*& operator[](std::string coord);
};


#endif