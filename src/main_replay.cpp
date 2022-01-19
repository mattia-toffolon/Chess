// Author: Guerrini Alberto

#ifndef REPLAY_CPP
#define REPLAY_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

#include "../include/Board.hpp"
#include "../include/Piece.hpp"

// NB:
// argv[argc] is a NULL pointer.
// argv[0] holds the name of the program.
// argv[1] points to the first command line argument and argv[n] points last argument

int main(int argc, char* argv[]) { 
    if(argc <= 2)
        throw std::invalid_argument("Too few command line argument: must be in format:\n\t- argument v [log_filename]: prints to cout the boards representing the logged match;\n\t- argument f [log_filename] [replay_filename]: prints into the replay file the logged match.\n");
    if(*argv[1] != 'v' && *argv[1] != 'f')
        throw std::invalid_argument("Can't recognize argument: must be in format:\n\t- argument v [log_filename]: prints to cout the boards representing the logged match;\n\t- argument f [log_filename] [replay_filename]: prints into the replay file the logged match.\n");
    if(*argv[1] == 'v' && argc != 3 || *argv[1] == 'f' && argc != 4 )
        throw std::invalid_argument("Wrong number of argument passed for: must be in format:\n\t- argument v [log_filename]: prints to cout the boards representing the logged match;\n\t- argument f [log_filename] [replay_filename]: prints into the replay file the logged match.\n");

    // at this point if no exeption has been trown, the parameters must be ok. But filename can be not found.
    // opening input log file
    std::ifstream in_file (argv[2]);
    if(!in_file.is_open())
        throw std::runtime_error("Input file is not open");

    // setting output file if it is requested
    std::ofstream out_file;
    if(*argv[1] == 'f')
        out_file.open(argv[3]);
    
    std::string temp;
    char promotion = 'N';
    const std::regex pattern ("[A-Ha-h][1-8][=][TCADtcad]");
    // read bottom player color
    in_file >> temp;
    std::string text = "BOTTOM_PLAYER=";
    // creating board having bottom player color
    Board board {(bool)(temp.at(text.length()) == '1')};
    // setting first player to start
    bool player_ID = Piece::WHITE;

    std::vector<std::string> moves;
    // iterate while the file ends
    while(in_file >> temp)
        moves.push_back(temp);
    in_file.close();

    int i = 0;
    while(i < moves.size()) {
        // check if there is a promotion
        // stores the position
        if(i+2 < moves.size())
            // if the next line is a promotion
            if(std::regex_match(moves.at(i+2), pattern))
                promotion = moves.at(i+2).at(3);
            else
                // if it is not a promotion revert the reading
                promotion = 'N';
        // if can't read: there is no promotion
        else
            promotion = 'N';

        // make the move
        try {
            board.move(moves.at(i), moves.at(i+1), player_ID, promotion);
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
        i = promotion!='N' ? i+3 : i+2;

        // change player color
        player_ID = !player_ID;
        if(*argv[1] == 'f')
            // print to file output
            out_file << board << std::endl;
        else{
            // print to cout
            std::cout << board << std::endl;
            // sleeps for one second
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
    // file strams closing
    if(out_file.is_open())
        out_file.close(); 
    return 0;
}

#endif