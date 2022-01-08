//Francesco Stella 2008816
#ifndef HUMAN_HPP
#define HUMAN_HPP
#include "Player.hpp"

class Human : public Player
{
public:
    //Call to the costructor of Player
    Human(bool ID, Board& b) : Player(ID, b){};
    //Function that control the turn
    void turn();
};

#endif  //HUMAN_HPP