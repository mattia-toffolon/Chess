//Francesco Stella 2008816
#ifndef PLAYER_CPP
#define PLAYER_CPP
#include<iostream>
#include "../include/Board.hpp"
#include "../include/Player.hpp"
#include "../include/King.hpp"

Player::Player(){};
//Costructor with argument ID for the color of the pawns
// and a reference to the chessboard
Player::Player(bool id, Board& b){
    ID = id;
    board = &b;
    check = false;
}

//Return the ID of the player
bool Player::get_ID(){
    return ID;
}

// sets check
void Player::set_check(bool c){
    check=c;
}

//returns check
bool Player::get_check(){
    return check;
}

//  checks if the move choosen by this player is safe for his King
bool Player::is_safe_move(const std::string& from, const std::string& to, const char promote){
    Board temp(*board);
    try{
        if(promote!='N')
            temp.move(from, to, ID);
        else    
            temp.move(from, to, ID, promote);
    }
    catch(CheckException e) {}
    King* k = dynamic_cast<King*>(temp.get_piece_at(12, ID));
    if(k->is_under_check(k->get_pos()))
        throw IllegalMoveException("The selected move is considered illegal: unsafe for this Player's King");
    else
        return true;
      
}

// returns a vector<string> containing all the possible moves
// for this Player to escape the check condition
std::vector<std::pair<std::string, std::string>> Player::get_safe_moves(){

    std::vector<std::pair<std::string, std::string>> ret;
    Piece* p;
    for(int i=0; i<Board::COLOR_OFFSET; i++){
        p = (*board).get_piece_at(i, ID);

        if(p == nullptr)
            continue;

        std::string from = p->get_pos();
        std::vector<std::string> possible_moves = p->get_possible_moves();

        for(std::string to : possible_moves){
            try{
                if(is_safe_move(from, to))
                    ret.push_back(std::make_pair(from, to));
            }
            catch(IllegalMoveException e){
                continue;
            }
        }
    }
    return ret;
}

#endif  //PLAYER_CPP