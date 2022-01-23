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

int main(){
    Match m(true);
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