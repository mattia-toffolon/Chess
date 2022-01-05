//Francesco Stella 2008816
#ifndef COMPUTER_HPP
#define COMPUTER_HPP
#include<iostream>
 
class Computer : public Player
{
public:
    //Costructor
    Computer();
    //Destructor
    ~Computer();
    void turn();
};

#endif  //COMPUTER_HPP