#include "../include/Board.hpp"
#include "../include/Piece.hpp"
#include <iostream>

int main(){
    // test
    Board b {Piece::WHITE};

    std::cout << "\n" << b << std::endl;

    try{
        b.move("A2", "A4", Piece::WHITE);
    }
    catch(IllegalMoveException e){
        std::cout<<e.what();
    }

    //b.move("A7", "A5", Piece::BLACK);

    std::cout << "\n" << b << std::endl;

    return 0;
}
