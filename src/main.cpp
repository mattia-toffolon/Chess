#include "../include/Board.hpp"
#include "../include/Piece.hpp"
#include <iostream>
#include <time.h>

int main(){
    // test
    Board b {Piece::WHITE};
    std::string from;
    std::string to;

    for(int i=1; i<11; i++){

        Piece* rand = &(b.get_random_piece(Piece::WHITE));

        std::cout<<i<<"   "<<(*rand).to_char()<<std::endl;

        std::vector<std::string> moves = (*rand).get_possible_moves();
        to = moves[std::rand() % moves.size()];
        from = (*rand).get_pos();

        std::cout<<from<<" "<<to<<std::endl;

        b.move(from, to, Piece::WHITE);
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
