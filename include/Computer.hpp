//Francesco Stella 2008816
#ifndef COMPUTER_HPP
#define COMPUTER_HPP
#include<iostream>
#include "Player.hpp"
 
class Computer : public Player
{
public:
    //Costructor
    Computer();
    //Function that control the turn
    void turn();
};

#endif  //COMPUTER_HPP