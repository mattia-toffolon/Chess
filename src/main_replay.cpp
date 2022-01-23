// Author: Guerrini Alberto

#ifndef REPLAY_CPP
#define REPLAY_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <deque>

#include "../include/Board.hpp"
#include "../include/Piece.hpp"

// NB:
// argv[argc] is a NULL pointer.
// argv[0] holds the name of the program.
// argv[1] points to the first command line argument and argv[n] points last argument

// helper functions declaration
void print(std::ifstream& in_file, std::ofstream& out_file);
char check_promotion(std::deque<std::string>& moves);

int main(int argc, char* argv[]) { 
    // check parameters and throw exception for invalid arguments
    if(argc <= 2)
        throw std::invalid_argument("Too few command line argument: must be in format:\n\t- argument v [log_filename]: prints to cout the boards representing the logged match;\n\t- argument f [log_filename] [replay_filename]: prints into the replay file the logged match.\n");
    if(*argv[1] != 'v' && *argv[1] != 'f')
        throw std::invalid_argument("Can't recognize argument: must be in format:\n\t- argument v [log_filename]: prints to cout the boards representing the logged match;\n\t- argument f [log_filename] [replay_filename]: prints into the replay file the logged match.\n");
    if(*argv[1] == 'v' && argc != 3 || *argv[1] == 'f' && argc != 4 )
        throw std::invalid_argument("Wrong number of argument passed for: must be in format:\n\t- argument v [log_filename]: prints to cout the boards representing the logged match;\n\t- argument f [log_filename] [replay_filename]: prints into the replay file the logged match.\n");

    // at this point if no exeption has been trown, the parameters must be ok. (filename can be not found)
    std::ifstream in_file (argv[2]);
    std::ofstream out_file;

    // opening input log file
    if(!in_file.is_open())
        throw std::runtime_error("Input file is not open, check if filename exist.");

    // setting output file if it is requested
    if(*argv[1] == 'f')
        out_file.open(argv[3]);

    // call function for print match
    print(in_file, out_file);

    // file streams closing
    if(out_file.is_open())
        out_file.close(); 
    in_file.close();
    
    return 0;
}

void print(std::ifstream& in_file, std::ofstream& out_file) {
    // variables for the while cicle
    std::string temp;
    bool file_has_next = true;
    char promotion = 'N';
    const int delay_time = 1000;
    // read bottom player color
    in_file >> temp;
    std::string text = "BOTTOM_PLAYER=";
    // creating board having bottom player color
    Board board ((bool)(temp.at(text.length()) == '1'), false);
    // setting first player to start
    bool player_ID = Piece::WHITE;
    // FIFO container to buffer strings that are read from input file
    // enqueue back and dequeue front
    std::deque<std::string> moves;

    while(!moves.empty() || file_has_next) {
        // enqueue from file 3 strings at time if there are
        // queue space complexity is O(n) having n = number of moves (every 3 enqueued, at least 2 are dequeued)
        if(file_has_next)
            for(short i = 0; i < 3 && file_has_next; i++) {
                if(in_file >> temp)
                    moves.push_back(temp);
                else
                    file_has_next = false;
            }

        // stores the moves coordinates and delete them from the queue
        std::string from = moves.front();
        moves.pop_front();
        std::string to = moves.front();
        moves.pop_front();
        // check if there is a promotion and make the move
        try {
            board.move(from, to, player_ID, check_promotion(moves));
        }
        catch(const std::exception& e) {}

        // change player color
        player_ID = !player_ID;
        // print to output file if it is open, else print to cout
        if(!out_file.is_open()) {
            std::cout << board << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
        }
        else
            out_file << board << std::endl;
    }
}

// checks if the next input is a promotion and return it
char check_promotion(std::deque<std::string>& moves) {
    std::regex pattern ("[A-Ha-h][1-8][=][TCADtcad]");
    if(!moves.empty())
        // if the next string have a promotion pattern remove it from the queue and return it
        if(std::regex_match(moves.front(), pattern)){
            char prom = moves.front().at(3);
            moves.pop_front();
            return prom;
            }
    return 'N';
}

#endif