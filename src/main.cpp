#include "../include/Board.hpp"
#include "../include/Piece.hpp"
#include <iostream>

int main(){
    // test
    Board b {Piece::WHITE};

    std::cout << "\n" << b << std::endl;

    try{
        b.move("A2", "A3", Piece::WHITE);
    }
    catch(IllegalMoveException e){
        std::cout<<e.what();
    }

    std::cout << "\n" << b << std::endl;

    return 0;
}
