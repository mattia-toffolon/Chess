//Francesco Stella 2008816
#include "../include/Board.hpp"
#include "../include/Piece.hpp"
#include "../include/King.hpp"
#include "../include/CheckException.hpp"
#include "../include/CheckMateException.hpp"
#include "../include/DrawException.hpp"
#include "../include/Computer.hpp"
#include "../include/Human.hpp"
#include "../include/Match.hpp"
#include <iostream>
#include <time.h>

int main(int argc, char* argv[]) { 

    if(argc != 2)
        throw std::invalid_argument("Wrong number of command line argument: must be in format:\n\t-  argument pc: starts a player vs computer match;\n\t-  argument cc: starts a computer vs computer match;\n");
    
    if( (*argv[1]!='p' && *argv[1]!='c') || *(argv[1]+1)!='c')
        throw std::invalid_argument("Wrong argument format:\n\t-  argument pc: starts a player vs computer match;\n\t-  argument cc: starts a computer vs computer match;\n");

    bool HumanPlayer;
    if(*argv[1]=='p')
        HumanPlayer=true;
    else    
        HumanPlayer=false;

    
    Match m(HumanPlayer);
    try{
        m.start();
    }
    catch(CheckMateException e){
        std::cout<<e.what()<<std::endl;
        return 0;
    }
    catch(DrawException e){
        std::cout<<e.what()<<std::endl;
        return 0;
    }
    
    return 0;
}