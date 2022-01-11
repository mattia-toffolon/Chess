#include "../include/Board.hpp"
#include <iostream>

int main(){
    // test
    Board a (true);
    a.move("A1","b1", true);
    a.operator<<(std::cout);

}