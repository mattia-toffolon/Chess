//Francesco Stella 2008816
#ifndef HUMAN_HPP
#define HUMAN_HPP
#include<iostream>
#include "Player.hpp"

class Human : public Player
{
public:
    //Costructor
    Human();
    //Destructor
    ~Human();
    void turn();
};

#endif  //HUMAN_HPP