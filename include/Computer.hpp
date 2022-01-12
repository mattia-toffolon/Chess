//Francesco Stella 2008816
#ifndef COMPUTER_HPP
#define COMPUTER_HPP
#include "Player.hpp"
#include "Board.hpp"
 
class Computer : public Player
{
public:
    //Call to the costructor of Player
    Computer(bool ID, Board& b) : Player(ID, b){};
    //Function that control the turn
    void turn();
};

#endif  //COMPUTER_HPP