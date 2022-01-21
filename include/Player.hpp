//Francesco Stella 2008816
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include<iostream>
#include "../include/Board.hpp"
#include "../include/CheckException.hpp"

class Player
{
protected:
    //Pointer to access the board
    Board* board;
    //Identifies the color of the Pieces that 
    //a player is going to use during the game
    bool ID;
    //determines if this Player is un undergoing check state
    bool check;
public:
    //Default Costructor
    Player();
    //Costructor with argument ID for the color of the pawns
    // and a reference to the chessboard
    Player(const bool ID, Board& b);
    //pure virtual function to manage each turn
    virtual void turn()=0;
    //Return the ID of the player
    bool get_ID();
    // sets check
    void set_check(bool c);
    // returns check
    bool get_check();
    // returns a vector<string> containing all the possible moves
    // for this Player to escape the check condition
    std::vector<std::pair<std::string, std::string>> get_escape_moves();
    //Invalidate copy costructor and copy assignement
    //to avoid slicing
    Player(Player&) = delete;
    Player& operator=(Player&) = delete;
};

//#include "../src/Player.cpp"

#endif  //PLAYER_HPP