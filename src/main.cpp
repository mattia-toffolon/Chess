#include "../include/Board.hpp"
#include "../include/Piece.hpp"
#include <iostream>
#include <time.h>

int main(){
    // test
    Board b {Piece::WHITE};
    std::string from;
    std::string to;
    std::cout<<b<<std::endl;

    srand(time(NULL));

    for(int i=1; i<11; i++){

        Piece* random_piece = b.get_random_piece(Piece::WHITE);

        while((*random_piece).get_possible_moves().empty())
            random_piece = b.get_random_piece(Piece::WHITE);

        std::vector<std::string> moves = (*random_piece).get_possible_moves();
        std::string to = moves[std::rand() % moves.size()];
        std::string from = (*random_piece).get_pos();

        b.move(from, to, Piece::WHITE);
        std::cout<<random_piece->to_char()<<" from: "<<from<<" to: "<<to<<std::endl;
        std::cout<<b<<std::endl;
    }

    /*
    try{
        b.move("b7","b5",Piece::BLACK);
    std::cout<<b;
    }
    catch(IllegalMoveException e){
        std::cout<<e.what();
    } */

    /*
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
    } */

    // try{
    //     b.move("A2", "A4", Piece::WHITE);
    // }
    // catch(IllegalMoveException e){
    //     std::cout<<e.what();
    // }

    //b.move("A7", "A5", Piece::BLACK);

    // std::cout << "\n" << b << std::endl;

    return 0;
}
