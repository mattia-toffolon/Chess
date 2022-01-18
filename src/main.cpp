#include "../include/Board.hpp"
#include "../include/Piece.hpp"
#include <iostream>

int main(){
    // test
    Board b {Piece::WHITE};
    std::string from;
    std::string to;

    b.move("e2","e3",Piece::WHITE);
    b.move("f1","c4",Piece::WHITE);

    std::cout<<b;

    std::cout<<b.get_piece_at(13, Piece::WHITE).get_pos()<<std::endl;

    std::vector<std::string> s = (b.get_piece_at(13, Piece::WHITE)).get_possible_moves();

    if(s.empty())
        std::cout<<"Vuoto e'\n";

    for(int i=0; i<s.size(); i++)
        std::cout<<s[i]<<" ";


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
