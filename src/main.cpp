#include "../include/Board.hpp"
#include "../include/Piece.hpp"
#include "../include/King.hpp"
#include "../include/CheckException.hpp"
#include <iostream>
#include <time.h>

int main(){
    // test
    Board b {Piece::WHITE};
    std::string from;
    std::string to;
    std::cout<<b<<std::endl<<std::endl;
    try{
        Board copy(b);
        std::cout<<copy<<std::endl;
    }
    catch(IllegalMoveException e){
        std::cerr<<e.what();
    }
    

    srand(time(NULL));

    /*
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
    } */

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
            std::cout<<b[from]->to_char()<<std::endl;

            try{
                b.move(from, to, Piece::WHITE);
            }
            catch(CheckException& e){}

            std::cout << std::endl << b << std::endl;
            
            
            King* k = dynamic_cast<King*>(b.get_piece_at(12, Piece::BLACK));
                
            if(k->is_under_check(k->get_pos())){
                if(k->get_possible_moves().empty())
                    std::cout<<"Scacco quasi-matto!\n";
                else    
                    std::cout<<"Il re avversario e' sotto scacco!\n";
            }

        }
        catch(IllegalMoveException& e)
        {
            std::cerr << e.what() << '\n';
        }
    } 
    */

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
