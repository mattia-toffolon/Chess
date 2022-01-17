#include "../include/Board.hpp"
#include "../include/Piece.hpp"
#include <iostream>

int main(){
    // test
    Board b {Piece::WHITE};
    std::string from;
    std::string to;

    try{
        b.move("b7","b5",Piece::BLACK);
    std::cout<<b;
    }
    catch(IllegalMoveException e){
        std::cout<<e.what();
    }

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
