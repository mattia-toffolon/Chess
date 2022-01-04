// Author: Guerrini Alberto

#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include "Piece.hpp"

class Board {
    
    private:
        static constexpr short DIM = 8;
        // contains references to all pieces:
        // [0,7] white pawn, [8,15] white other pieces (in the order from left to right in the board)
        // [16,23] white pawn, [24,31] white other pieces (in the order from left to right in the board)
        std::vector<Piece*> pieces_;
        // represents the dashboard, it starts having in the first rows the pieces of the player
        std::vector<std::vector<Piece*>> dashboard_;

    public:
        Board(bool player_color) {
           for (int i = 0; i < DIM; i++) {
               
           }
            
        }
};


#endif