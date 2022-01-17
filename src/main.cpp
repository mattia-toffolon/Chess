#include "../include/Board.hpp"
#include "../include/Piece.hpp"
#include <iostream>

int main(){
    // test
    Board b {Piece::WHITE};

    std::cout << "\n" << b << std::endl;

    return 0;
}
