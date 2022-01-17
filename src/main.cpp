#include "../include/Board.hpp"
#include "../include/Piece.hpp"
#include <iostream>

int main(){
    // test
    Board b {Piece::WHITE};
    std::string from;
    std::string to;

    while(true){
        std::cout << std::endl <<"Mossa: ";
        std::cin >> from;
        std::cin >> to;
        try
        {
            b.move(from, to, Piece::WHITE);
        }
        catch(IllegalMoveException& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << std::endl << b << std::endl;
    }

    return 0;
}
